#include "VisionSubsystem.h"
#include "Robot.h"
#include "Math.h"
using namespace CORE;

VisionSubsystem::VisionSubsystem() : CORESubsystem("Vision"),
	gearPlaceDist("Gear Place Distance", 12),
	ultrakP("Ultrasonic kP", .3),
	m_imageWidth("Image width", 1280),
	m_horizontalFieldOfView("Horizontal field of view", 50.5),
	m_ultra(GEAR_ULTRA_PORT),
	m_jumper(JUMPER_PORT){

}

void VisionSubsystem::robotInit(){
	Robot->operatorJoystick.registerButton(COREJoystick::BACK_BUTTON);
	visionTable = NetworkTable::GetTable("Vision");
	visionTable->PutNumber("piTime", -1);
	visionTable->PutNumber("targetX", -1);
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
	x = m_imageWidth.Get() - x;

	if(x == -1 || m_lastPiTime == piTime){
		return;
	}

	double captureTime = visionTable->GetNumber("piTime", -1) + m_timeOffset;

	Position2d capturePos = TankTracker::GetInstance()->getFieldToVehicle(captureTime-.5);
	Rotation2d captureRot = capturePos.getRotation();

	double focalLen = m_imageWidth.Get() / (2 * tan(CORE::toRadians(m_horizontalFieldOfView.Get() * .5)));
	double hAngle = atan((x-(m_imageWidth.Get() * .5 - .5)) / focalLen);

	m_targetRotation = captureRot.rotateBy(Rotation2d::fromRadians(hAngle));
}

Rotation2d VisionSubsystem::getError(){
	Rotation2d current = TankTracker::GetInstance()->getLatestFieldToVehicle().getRotation();
	Rotation2d target = m_targetRotation;
	return target.rotateBy(current.inverse());
}

double VisionSubsystem::getUltraDist() {
	double scale = (1024.0 / 2.54); //403.1496
	return (1000.0 * m_ultra.GetVoltage()) / ((m_jumper.GetVoltage() * 1000.0) / scale);
}
