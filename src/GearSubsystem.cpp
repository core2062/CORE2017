#include "GearSubsystem.h"
#include "Robot.h"

using namespace CORE;

GearSubsystem::GearSubsystem() : CORESubsystem("Gear"),
								m_punchSolenoid(PUNCH_SOLENOID_PCM, PUNCH_SOLENOID_OUT_PORT, PUNCH_SOLENOID_IN_PORT),
								m_leftFlapSolenoid(LEFT_GEAR_FLAP_SOLENOID_PCM, LEFT_GEAR_FLAP_SOLENOID_OUT_PORT, LEFT_GEAR_FLAP_SOLENOID_IN_PORT),
								m_rightFlapSolenoid(RIGHT_GEAR_FLAP_SOLENOID_PCM, RIGHT_GEAR_FLAP_SOLENOID_OUT_PORT, RIGHT_GEAR_FLAP_SOLENOID_IN_PORT),
								m_punchTime("Punch Out Time", 1.5) {
	CORELog::logInfo("Gear subsystem constructor!");
}

void GearSubsystem::robotInit() {
	Robot->operatorJoystick.registerButton(COREJoystick::LEFT_BUTTON);
	Robot->operatorJoystick.registerButton(COREJoystick::RIGHT_BUTTON);

}

void GearSubsystem::teleopInit() {
	m_leftFlapSolenoid.Set(DoubleSolenoid::kForward);
	m_rightFlapSolenoid.Set(DoubleSolenoid::kForward);
}

void GearSubsystem::teleop(){
	if (Robot->operatorJoystick.getButtonState(COREJoystick::LEFT_BUTTON) == COREJoystick::RISING_EDGE) {
		if (flapIsOpen()){
			closeFlap();
		}else{
			openFlap();
		}
	}

	if (Robot->operatorJoystick.getRisingEdge(COREJoystick::RIGHT_BUTTON)){
		punchOut();
	}
	if(checkPunchShouldClose()){
		punchIn();
	}

}

void GearSubsystem::punchOut() {
	m_punchSolenoid.Set(DoubleSolenoid::kForward);
	m_punchTimer.Reset();
	m_punchTimer.Start();
}

void GearSubsystem::punchIn() {
	m_punchSolenoid.Set(DoubleSolenoid::kReverse);
}

bool GearSubsystem::checkPunchShouldClose() {
	return (m_punchTimer.Get() > m_punchTime.Get());
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
