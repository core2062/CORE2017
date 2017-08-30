#include "Robot.h"

#ifdef GEAR_PICKUP

#include "GearPickupSubsystem.h"

using namespace CORE;

GearSubsystem::GearSubsystem() :
//								m_leftManipulatorSolenoid(GEAR_PICKUP_LEFT_PCM, GEAR_PICKUP_LEFT_OUT_PORT, GEAR_PICKUP_LEFT_IN_PORT),
//								m_rightManipulatorSolenoid(GEAR_PICKUP_RIGHT_PCM, GEAR_PICKUP_RIGHT_OUT_PORT, GEAR_PICKUP_RIGHT_IN_PORT),
//								m_out(GEAR_PICKUP_RIGHT_PCM,GEAR_PICKUP_RIGHT_OUT_PORT),
//								m_in(GEAR_PICKUP_RIGHT_PCM,GEAR_PICKUP_RIGHT_IN_PORT),
								m_manipulatorForwardSolenoid(GEAR_PICKUP_FORWARD_PCM, GEAR_PICKUP_FORWARD_ON_PORT, GEAR_PICKUP_FORWARD_OFF_PORT),
								m_manipulatorReverseSolenoid(GEAR_PICKUP_REVERSE_PCM, GEAR_PICKUP_REVERSE_ON_PORT, GEAR_PICKUP_REVERSE_OFF_PORT),
								m_leftFlapSolenoid(LEFT_GEAR_FLAP_SOLENOID_PCM, LEFT_GEAR_FLAP_SOLENOID_OUT_PORT, LEFT_GEAR_FLAP_SOLENOID_IN_PORT),
								m_rightFlapSolenoid(RIGHT_GEAR_FLAP_SOLENOID_PCM, RIGHT_GEAR_FLAP_SOLENOID_OUT_PORT, RIGHT_GEAR_FLAP_SOLENOID_IN_PORT),
								m_rollerMotor(GEAR_INTAKE_PORT),
								m_actuateTime("Gear Pickup Actuation Time", .2),
								m_reverseRollerTime("Gear Place Roller Delay", .05){
	CORELog::logInfo("Gear subsystem constructor!");
}

void GearSubsystem::robotInit() {
	Robot->operatorJoystick.registerButton(COREJoystick::LEFT_BUTTON);
	Robot->operatorJoystick.registerButton(COREJoystick::RIGHT_BUTTON);
	Robot->operatorJoystick.registerAxis(COREJoystick::RIGHT_TRIGGER_AXIS);
	Robot->operatorJoystick.registerAxis(COREJoystick::LEFT_TRIGGER_AXIS);
	Robot->gearSubsystem.openFlap();

}

void GearSubsystem::teleopInit() {
//	m_leftFlapSolenoid.Set(DoubleSolenoid::kForward);
//	m_rightFlapSolenoid.Set(DoubleSolenoid::kForward);
//	m_leftFlapSolenoid.Set(DoubleSolenoid::kReverse);
//	m_rightFlapSolenoid.Set(DoubleSolenoid::kReverse);
}

void GearSubsystem::teleop(){
	if (Robot->operatorJoystick.getRisingEdge(COREJoystick::LEFT_BUTTON)) {
		if (flapIsOpen()) {
			closeFlap();
		} else if ((Robot->hopperSubsystem.liftGearFlapPos.Get() - 100) > Robot->hopperSubsystem.getLiftPos()) {
			openFlap();
		}
	}
	double intakeButton = Robot->operatorJoystick.getAxis(COREJoystick::RIGHT_TRIGGER_AXIS);

	if(Robot->operatorJoystick.getRisingEdge(COREJoystick::RIGHT_BUTTON)){
		if(m_state == GearPickupState::HOLDING){
			placeGear();
		} else {
			holdIn();
		}
	} else if (intakeButton >= .1 && oldIntakeButton < .1){
		pickupGear();
	} else if (intakeButton < .1 && oldIntakeButton >= .1){
		safePickup();
	}  else if (Robot->operatorJoystick.getAxis(COREJoystick::LEFT_TRIGGER_AXIS) > .1){
		feed();
	} else if (m_state != GearPickupState::PICKUP && m_state != GearPickupState::PLACING && m_state != GearPickupState::PICKINGUP){
		holdIn();
	}

	oldIntakeButton = intakeButton;
}

void GearSubsystem::teleopEnd() {
	pickupOff();
}

void GearSubsystem::placeGear() {
	m_placeTimer.Reset();
	m_placeTimer.Start();
	m_state = GearPickupState::PLACING;
}

void GearSubsystem::autoPlaceGear() {
	m_placeTimer.Reset();
	m_placeTimer.Start();
	m_state = GearPickupState::AUTOPLACING;
}

void GearSubsystem::pickupGear() {
	m_placeTimer.Reset();
	m_placeTimer.Start();
	m_state = GearPickupState::PICKUP;
	std::cout << "PickupGear" << std::endl;
}

void GearSubsystem::holdIn() {
	m_state = GearPickupState::HOLDING;
}

void GearSubsystem::safePickup() {
	m_placeTimer.Reset();
	m_placeTimer.Start();
	m_state = GearPickupState::PICKINGUP;
}

void GearSubsystem::feed() {
	m_state = GearPickupState::FEEDING;
}

void GearSubsystem::pickupIn() {
//	m_leftManipulatorSolenoid.Set(DoubleSolenoid::kReverse);
//	m_rightManipulatorSolenoid.Set(DoubleSolenoid::kReverse);
	m_manipulatorForwardSolenoid.Set(DoubleSolenoid::kReverse);
	m_manipulatorReverseSolenoid.Set(DoubleSolenoid::kForward);
//	m_out.Set(false);
//	m_in.Set(true);
}

void GearSubsystem::pickupOut() {
//	m_leftManipulatorSolenoid.Set(DoubleSolenoid::kForward);
//	m_rightManipulatorSolenoid.Set(DoubleSolenoid::kForward);
	m_manipulatorReverseSolenoid.Set(DoubleSolenoid::kReverse);
	m_manipulatorForwardSolenoid.Set(DoubleSolenoid::kForward);
	//	m_in.Set(false);
//	m_out.Set(true);
}

void GearSubsystem::pickupOff() {
//	m_leftManipulatorSolenoid.Set(DoubleSolenoid::kOff);
//	m_rightManipulatorSolenoid.Set(DoubleSolenoid::kOff);
	m_manipulatorReverseSolenoid.Set(DoubleSolenoid::kReverse);
	m_manipulatorForwardSolenoid.Set(DoubleSolenoid::kReverse);
}

void GearSubsystem::setRoller(double val) {
	m_rollerMotor.Set(val);
}


void GearSubsystem::openFlap(){
	m_leftFlapSolenoid.Set(DoubleSolenoid::kReverse);
	m_rightFlapSolenoid.Set(DoubleSolenoid::kReverse);
}

void GearSubsystem::closeFlap(){
	m_leftFlapSolenoid.Set(DoubleSolenoid::kForward);
	m_rightFlapSolenoid.Set(DoubleSolenoid::kForward);
}

bool GearSubsystem::flapIsOpen(){
	return (m_leftFlapSolenoid.Get() != DoubleSolenoid::kForward);
}

GearPickupState GearSubsystem::getState(){
	return m_state;
}

void GearSubsystem::postLoopTask() {
	switch(m_state){
	case(GearPickupState::HOLDING):
		pickupIn();
		setRoller(0);
		break;
	case(GearPickupState::FEEDING):
		pickupIn();
//		pickupOff();
		setRoller(-1.0);
		break;
	case(GearPickupState::PICKUP):
		if(m_placeTimer.Get() < m_actuateTime.Get()){
			pickupOut();
		} else {
			pickupOff();
		}
//		pickupOut();
		setRoller(-1.0);
		break;
	case(GearPickupState::PLACING):
		if(m_placeTimer.Get() < m_reverseRollerTime.Get()){
			setRoller(0);
		} else {
			setRoller(1.0);
		}
		pickupOut();
//		if(m_placeTimer.Get() > m_placeTime.Get()){
//			m_state = GearPickupState::HOLDING;
//		}
		break;
	case(GearPickupState::AUTOPLACING):
		if(m_placeTimer.Get() < m_reverseRollerTime.Get()){
			setRoller(0);
		} else {
			setRoller(1.0);
		}
		pickupOut();
		if(m_placeTimer.Get() > 1){
			m_state = GearPickupState::HOLDING;
		}
		break;
	case(GearPickupState::PICKINGUP):
		if(m_placeTimer.Get() < m_actuateTime.Get()*3){
			setRoller(-1.0);
		}else{
			holdIn();
		}
		pickupIn();
//		if(m_placeTimer.Get() > m_placeTime.Get()){
//			m_state = GearPickupState::HOLDING;
//		}
		break;
	}
}



#endif
