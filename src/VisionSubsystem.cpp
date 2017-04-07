#include "VisionSubsystem.h"
#include "Robot.h"

using namespace CORE;

VisionSubsystem::VisionSubsystem() : CORESubsystem("Vision"),
	m_imageWidth("Image width", 1280),
	m_imageHeight("Image height", 720),
	m_cameraPegDeltaH("Camera height above the target", 8),
	m_verticalFieldOfView("Vertical field of view", 40),
	m_horizontalFieldOfView("Horizontal field of view", 66),
	m_pegPlaceDist("Peg Place Distance", 12),
	m_pegApproachDist("Peg Approach Distance", 24),
	m_pegApproachSamples("Peg Approach Samples", 3){

}

void VisionSubsystem::robotInit(){
	Robot->operatorJoystick.registerButton(COREJoystick::BACK_BUTTON);
	visionTable = NetworkTable::GetTable("Vision");
	visionTable->PutNumber("piTime", -1);
}

void VisionSubsystem::teleopInit(){

}
void VisionSubsystem::teleop() {
	if (Robot->operatorJoystick.getRisingEdge(COREJoystick::BACK_BUTTON)){
		//if the right button is pressed, switch the front camera to the gear camera
		if (whichCamera == frontCamera){
			whichCamera = gearCamera;
		}else{
			whichCamera = frontCamera;
		}
	}
	visionTable->PutString("camera", whichCamera);
}

void VisionSubsystem::preLoopTask() {
	if(m_timeOffsets.size() < 30){
		double piTime = visionTable->GetNumber("piTime", -1);
		if(piTime != -1){
			double botTime = Timer::GetFPGATimestamp();
			m_timeOffsets.push_back(botTime - piTime);
			m_timeOffset = 0;
			for(auto i : m_timeOffsets){
				m_timeOffset+=i;
			}
			m_timeOffset /= m_timeOffsets.size();
		}
	}
}

Path * VisionSubsystem::getPath() {
	return &m_pathToPeg;
}

RobotFrame * VisionSubsystem::getFrame(){
	return &m_visionFrame;
}

void VisionSubsystem::calculatePath() {
	double x = visionTable->GetNumber("targetX", -1);
	double y = visionTable->GetNumber("targetY", -1);

	double captureTime = visionTable->GetNumber("captureTime", -1) - m_timeOffset;
	Position2d capturePos = TankTracker::GetInstance()->getFieldToVehicle(captureTime);
	double captureRot = capturePos.getRotation().getDegrees();

	Rotation2d coordRot;

	if(captureRot > -29 && captureRot < 29){
		coordRot = capturePos.getRotation();
		m_visionFrame = RobotFrame(Position2d(capturePos.getTranslation(), Rotation2d::fromDegrees(0)));
	} else if (captureRot > 31 && captureRot < 89){
		coordRot = Rotation2d::fromDegrees(60).rotateBy(capturePos.getRotation());
		m_visionFrame = RobotFrame(Position2d(capturePos.getTranslation(), Rotation2d::fromDegrees(60)));
	} else if (captureRot > -89 && captureRot < -31){
		coordRot = Rotation2d::fromDegrees(-60).rotateBy(capturePos.getRotation());
		m_visionFrame = RobotFrame(Position2d(capturePos.getTranslation(), Rotation2d::fromDegrees(-60)));
	}

	double focalLen = m_imageWidth.Get() / (2 * tan(CORE::toRadians(m_horizontalFieldOfView.Get() * .5)));
	double hAngle = atan((x-(m_imageWidth.Get() * .5 - .5)) / focalLen);
	double vAngle = atan((y-(m_imageHeight.Get() * .5 - .5)) / focalLen);
	double distToPeg = m_cameraPegDeltaH.Get() / tan(vAngle);
	double forward = cos(hAngle) * distToPeg;
	double side = sin(hAngle) * distToPeg;

	Translation2d pegPos(-forward,side);
	pegPos = pegPos.rotateBy(coordRot);

	//MATH

	std::vector<Waypoint> points;
	points.push_back(Waypoint(Translation2d(),100));
	int samples = m_pegApproachSamples.Get();
	double sampleDelta = (m_pegPlaceDist.Get() - m_pegApproachDist.Get()) / (double)samples;
	for(int i = samples; i >= 0; i ++){
		points.push_back(Waypoint(Translation2d(pegPos.getX() + m_pegPlaceDist.Get() + sampleDelta * i,
				pegPos.getY()), 100));
	}
	m_pathToPeg = Path(points);


}

















