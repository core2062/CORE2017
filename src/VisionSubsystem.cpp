#include "VisionSubsystem.h"
#include "Robot.h"
#include "Math.h"
using namespace CORE;

VisionSubsystem::VisionSubsystem() : CORESubsystem("Vision"),
	gearPlaceDist("Gear Place Distance", 12),
	ultrakP("Ultrasonic kP", .03),
	m_imageWidth("Image width", 640),
	m_horizontalFieldOfView("Horizontal field of view", 48.8),
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

	if(m_lastPiTime == piTime){
		return;
	}
	Position2d capturePos = TankTracker::GetInstance()->getLatestFieldToVehicle();
	Rotation2d captureRot = capturePos.getRotation();

	double focalLen = m_imageWidth.Get() / (2 * tan(CORE::toRadians(m_horizontalFieldOfView.Get() * .5)));
	double hAngle = atan((x-(m_imageWidth.Get() * .5 - .5)) / focalLen);

	m_targetRotation = captureRot.rotateBy(Rotation2d::fromRadians(hAngle));
//	std::cout << "LU: " << m_leftUltra.GetVoltage() << " RU: " << m_rightUltra.GetVoltage() <<
//			" J: " << m_jumper.GetVoltage() << " D: " << getUltraDist() << std::endl;
}

Rotation2d VisionSubsystem::getError(){
	Rotation2d current = TankTracker::GetInstance()->getLatestFieldToVehicle().getRotation();
	Rotation2d target = m_targetRotation;
	return target.rotateBy(current.inverse());
}

double VisionSubsystem::getErrorPercent() {
	return (m_pegX - (m_imageWidth.Get() * .5)) / m_imageWidth.Get();
}

double VisionSubsystem::getUltraDist() {
	double scale = (1024.0 / 2.54); //403.1496
	return (1000.0 * .5 * (m_leftUltra.GetVoltage() + m_rightUltra.GetVoltage())) / ((m_jumper.GetVoltage() * 1000.0) / scale);
}
