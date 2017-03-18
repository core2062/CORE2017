#include "VisionSubsystem.h"
#include "Robot.h"

using namespace CORE;

VisionSubsystem::VisionSubsystem() : CORESubsystem("Vision"){

}

void VisionSubsystem::robotInit(){
	Robot->driverJoystick.registerButton(COREJoystick::RIGHT_BUTTON);
	visionTable = NetworkTable::GetTable("Vision");
}

void VisionSubsystem::teleopInit(){

}
void VisionSubsystem::teleop() {
	if (Robot->driverJoystick.getRisingEdge(COREJoystick::RIGHT_BUTTON)){
		//if the right button is pressed, switch the front camera to the gear camera
		if (whichCamera == frontCamera){
			whichCamera = gearCamera;
		}else{
			whichCamera = frontCamera;
		}
	}
	visionTable->PutString("camera", whichCamera);
}


