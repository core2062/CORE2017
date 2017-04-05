#include "Robot.h"

#ifdef GEAR_PICKUP

#include "GearPickupSubsystem.h"

using namespace CORE;

GearSubsystem::GearSubsystem() : CORESubsystem("Gear"),
								m_leftManipulatorSolenoid(GEAR_PICKUP_LEFT_PCM, GEAR_PICKUP_LEFT_OUT_PORT, GEAR_PICKUP_LEFT_IN_PORT),
								m_rightManipulatorSolenoid(GEAR_PICKUP_RIGHT_PCM, GEAR_PICKUP_RIGHT_OUT_PORT, GEAR_PICKUP_RIGHT_IN_PORT),
								m_leftFlapSolenoid(LEFT_GEAR_FLAP_SOLENOID_PCM, LEFT_GEAR_FLAP_SOLENOID_OUT_PORT, LEFT_GEAR_FLAP_SOLENOID_IN_PORT),
								m_rightFlapSolenoid(RIGHT_GEAR_FLAP_SOLENOID_PCM, RIGHT_GEAR_FLAP_SOLENOID_OUT_PORT, RIGHT_GEAR_FLAP_SOLENOID_IN_PORT),
								m_rollerMotor(GEAR_INTAKE_PORT, VICTOR),
								m_placeTime("Gear Placing Time", .5),
								m_reverseRollerTime("Gear Place Roller Delay", .1){
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
	if(m_state != GearPickupState::PLACING){
		if(Robot->operatorJoystick.getRisingEdge(COREJoystick::RIGHT_BUTTON)){
			placeGear();
		} else if (Robot->operatorJoystick.getAxis(COREJoystick::RIGHT_TRIGGER_AXIS)){
			pickupGear();
		} else if (Robot->operatorJoystick.getAxis(COREJoystick::LEFT_TRIGGER_AXIS)){
			feed();
		} else {
			holdIn();
		}
	}

}


void GearSubsystem::placeGear() {
	m_state = GearPickupState::PLACING;
}

void GearSubsystem::pickupGear() {
	m_state = GearPickupState::PICKUP;
}

void GearSubsystem::holdIn() {
	m_state = GearPickupState::HOLDING;
}

void GearSubsystem::feed() {
	m_state = GearPickupState::FEEDING;
}

void GearSubsystem::pickupIn() {
	m_leftManipulatorSolenoid.Set(DoubleSolenoid::kReverse);
	m_rightManipulatorSolenoid.Set(DoubleSolenoid::kReverse);
}

void GearSubsystem::pickupOut() {
	m_leftManipulatorSolenoid.Set(DoubleSolenoid::kForward);
	m_rightManipulatorSolenoid.Set(DoubleSolenoid::kForward);
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
		setRoller(-.5);
		break;
	case(GearPickupState::PICKUP):
		pickupOut();
		setRoller(-1.0);
		break;
	case(GearPickupState::PLACING):
		if(m_placeTimer.Get() < m_reverseRollerTime.Get()){
			setRoller(-.1);
		} else {
			setRoller(1.0);
		}
		pickupOut();
		if(m_placeTimer.Get() > m_placeTime.Get()){
			m_state = GearPickupState::HOLDING;
		}
	}
}

#endif
