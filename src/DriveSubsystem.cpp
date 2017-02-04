#include "DriveSubsystem.h"
#include "Robot.h"

DriveSubsystem::DriveSubsystem() : CORESubsystem("Drive Subsystem"), m_etherAValue("Ether A Value", 1),
                                   m_etherBValue("Ether B Value", 1), m_etherQuickTurnValue("Ether Quick Turn Value", 2),
                                   m_FRDrive(10), m_BRDrive(11), m_BLDrive(12), m_FLDrive(13),
                                   m_drive(&m_BLDrive, &m_FLDrive, &m_BRDrive, &m_FRDrive, m_etherAValue.Get(),
                                           m_etherBValue.Get(),m_etherQuickTurnValue.Get()), m_driveShifter() {

}

void DriveSubsystem::robotInit() {
	m_FRDrive.setReversed(false);
	m_BRDrive.setReversed(false);
	m_BLDrive.setReversed(false);
	m_FLDrive.setReversed(false);
}

void DriveSubsystem::teleopInit() {

}

void DriveSubsystem::teleop() {
    double y = Robot::driverJoystick->getAxis(COREJoystick::LEFT_STICK_Y);
    double rot = Robot::driverJoystick->getAxis(COREJoystick::RIGHT_STICK_X);
    m_drive.cartesian(0, y, rot);
}
