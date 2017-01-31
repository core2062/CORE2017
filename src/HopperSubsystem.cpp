#include "HopperSubsystem.h"

HopperSubsystem::HopperSubsystem() : CORESubsystem("Hopper"), liftMotor(14), dumpFlap(1, 2),
									liftPID(&liftMotor, &liftMotor, POS_VEL, 0, 0, 0) {

}

void HopperSubsystem::robotInit(){

}

void HopperSubsystem::teleopInit(){

}

void HopperSubsystem::teleop(){
	if (true /*hopperButtonIsPressed*/){
		if (flapIsOpen()){
			closeFlap();
		}else {
			openFlap();
		}
	}
}

void HopperSubsystem::setLiftTop(){
	liftPID.setPos(TOP_LIMIT);
	liftPID.setVel(RAISE_LIMIT);

}

void HopperSubsystem::setLiftBottom(){
	liftPID.setPos(BOTTOM_LIMIT);
	liftPID.setVel(LOWER_LIMIT);

}

void HopperSubsystem::openFlap(){
	dumpFlap.Set(DoubleSolenoid::kForward);
}

void HopperSubsystem::closeFlap(){
	dumpFlap.Set(DoubleSolenoid::kReverse);
}


bool HopperSubsystem::flapIsOpen(){
	if (dumpFlap.Get() == DoubleSolenoid::kForward)
		return true;
	 else
		 return false;
}
