#include "VisionSubsystem.h"
#include "Robot.h"
#include "Math.h"
using namespace CORE;

VisionSubsystem::VisionSubsystem() : CORESubsystem("Vision"),
	gearPlaceDist("Gear Place Distance", 12),
	ultrakP("Ultrasonic kP", .03),
	m_imageWidth("Image width", 640),
	m_horizontalFieldOfView("Horizontal field of view", 60),
	m_pegApproachDist("Peg Approach Distance", 24),
	m_pegApproachSamples("Peg Approach Samples", 10),
	m_leftUltra(4),
	m_rightUltra(5),
	m_jumper(6){

}

void VisionSubsystem::robotInit(){
	Robot->operatorJoystick.registerButton(COREJoystick::BACK_BUTTON);
	visionTable = NetworkTable::GetTable("Vision");
	visionTable->PutNumber("piTime", -1);
	visionTable->PutNumber("targetX", -1);
	visionTable->PutBoolean("disableGearVision", true);
	visionTable->PutBoolean("disablePegVision", false);
	visionTable->PutBoolean("disableVision", false);
}

void VisionSubsystem::teleopInit(){
	visionTable->PutBoolean("disablePegVision", true);
	visionTable->PutBoolean("disableVision", true);
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
	SmartDashboard::PutNumber("Ultra Distance", getUltraDist());
	double piTime = visionTable->GetNumber("piTime", -1);
	if(m_timeOffsets.size() < 30){
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

	double x = visionTable->GetNumber("targetX", -1);
	if(x == -1){
		m_pegX = m_imageWidth.Get() * .5;
		return;
	}
//	x = m_imageWidth.Get() - x;

	m_pegX = x;
}

Path * VisionSubsystem::getPath() {
	return &m_pathToPeg;
}

RobotFrame * VisionSubsystem::getFrame(){
	return &m_visionFrame;
}

void VisionSubsystem::calculatePath() {
	double x = visionTable->GetNumber("targetX", -1);

//	double x = 1000;
//	double y = 450;



	x = m_imageWidth.Get() - x;

	if(x == -1){
		x = m_imageWidth.Get() * .5;
		CORELog::logWarning("Couldn't See Vision Target!");
	}

	Position2d capturePos = TankTracker::GetInstance()->getLatestFieldToVehicle();
	double captureRot = capturePos.getRotation().getDegrees();
	std::cout << "X:" << capturePos.getTranslation().getX() << " Y:" <<
			capturePos.getTranslation().getY() << " T:" << capturePos.getRotation().getDegrees() << std::endl;

	Rotation2d coordRot;

	if(captureRot > -29 && captureRot < 29){
		coordRot = capturePos.getRotation();
		m_visionFrame = RobotFrame(Position2d(capturePos.getTranslation(), Rotation2d::fromDegrees(0)));
	} else if (captureRot > 31 && captureRot < 89){
		coordRot = capturePos.getRotation().rotateBy(Rotation2d::fromDegrees(-60));
		m_visionFrame = RobotFrame(Position2d(capturePos.getTranslation(), Rotation2d::fromDegrees(-60)));
	} else if (captureRot > -89 && captureRot < -31){
//		coordRot = Rotation2d::fromDegrees(-60).rotateBy(capturePos.getRotation().inverse());
		coordRot = capturePos.getRotation().rotateBy(Rotation2d::fromDegrees(60));
		m_visionFrame = RobotFrame(Position2d(capturePos.getTranslation(), Rotation2d::fromDegrees(60)));
	}

	std::cout << "deltaRot: " << coordRot.getDegrees() << std::endl;

	double focalLen = m_imageWidth.Get() / (2 * tan(CORE::toRadians(m_horizontalFieldOfView.Get() * .5)));
	double hAngle = atan((x-(m_imageWidth.Get() * .5 - .5)) / focalLen);
	double distToPeg = getUltraDist();
	double forward = cos(hAngle) * distToPeg;
	double side = sin(hAngle) * distToPeg;

	Translation2d pegPos(-forward,-side);
	std::cout << "FWD: " << pegPos.getX() << " SIDE: " << pegPos.getY() << std::endl;
	pegPos = pegPos.rotateBy(coordRot);
	std::cout << "FWD: " << pegPos.getX() << " SIDE: " << pegPos.getY() << std::endl;

	//MATH
	std::cout << "About To generate points, x at" << pegPos.getX() << std::endl;
	std::vector<Waypoint> points;
	points.push_back(Waypoint(Translation2d(),100));
	int samples = m_pegApproachSamples.Get();
	std::cout << "Taking " << samples << " Samples" << std::endl;
	double sampleDelta = fabs(gearPlaceDist.Get() - m_pegApproachDist.Get()) / (double)samples;
	for(int i = samples; i >= 0; i--){
		points.push_back(Waypoint(Translation2d(pegPos.getX() + gearPlaceDist.Get() + sampleDelta * i,
				pegPos.getY()), 100));
	}
	m_pathToPeg = Path(points);

	for(auto i : points){
		std::cout << "X:" << i.position.getX() << " Y:" << i.position.getY() << " Speed:" << i.speed << std::endl;
	}

	std::cout << "Done Calcing Vision" << std::endl;


}

Rotation2d VisionSubsystem::getError(){
	Rotation2d current = TankTracker::GetInstance()->getLatestFieldToVehicle().getRotation();
	Rotation2d target = m_targetRotation;
	return target.rotateBy(current.inverse());
}

double VisionSubsystem::getErrorPercent() {
	return (m_pegX - (m_imageWidth.Get() * .5)) / m_imageWidth.Get();
}

void VisionSubsystem::autonInitTask() {
	visionTable->PutBoolean("disablePegVision", false);
	visionTable->PutBoolean("disableVision", false);
}

double VisionSubsystem::getUltraDist() {
	double scale = (1024.0 / 2.54); //403.1496
	double l = (1000.0 * (m_leftUltra.GetVoltage())) / ((m_jumper.GetVoltage() * 1000.0) / scale);
	double r = (1000.0 * (m_rightUltra.GetVoltage())) / ((m_jumper.GetVoltage() * 1000.0) / scale);
	double v;
	if(abs(l-r) > 10){
		if(l>r){
			v = r;
		} else {
			v = l;
		}
	}else{
		v = (l + r) * .5;
	}
	return v;
}
