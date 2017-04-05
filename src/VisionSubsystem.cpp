#include "VisionSubsystem.h"
#include "Robot.h"

using namespace CORE;

VisionSubsystem::VisionSubsystem() : CORESubsystem("Vision"),
	m_imageWidth("Image width", 1280),
	m_imageHeight("Image height", 720),
	m_cameraPegDeltaH("Camera height above the target", 8),
	m_verticalFieldOfView("Vertical field of view", 40),
	m_horizontalFieldOfView("Horizontal field of view", 66){

}

void VisionSubsystem::robotInit(){
	Robot->operatorJoystick.registerButton(COREJoystick::BACK_BUTTON);
//	visionTable = NetworkTable::GetTable("Vision");
//	visionTable->PutNumber("piTime", -1);
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
//	visionTable->PutString("camera", whichCamera);
}

void VisionSubsystem::preLoopTask() {
	double x;
	double y;



	if(m_timeOffsets.size() < 30){
		//double piTime = visionTable->GetNumber("piTime", -1);
		double piTime = -1.0;
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
