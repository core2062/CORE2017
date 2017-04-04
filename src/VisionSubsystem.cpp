#include "VisionSubsystem.h"
#include "Robot.h"

using namespace CORE;

VisionSubsystem::VisionSubsystem() : CORESubsystem("Vision"){

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
