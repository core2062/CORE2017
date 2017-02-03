#include "DriveSubsystem.h"
#include "Robot.h"

DriveSubsystem::DriveSubsystem() : CORESubsystem("Drive Subsystem"),
									m_FRDrive(FR_DRIVE_MOTOR_PORT),
									m_BRDrive(BR_DRIVE_MOTOR_PORT),
									m_BLDrive(BL_DRIVE_MOTOR_PORT),
									m_FLDrive(FL_DRIVE_MOTOR_PORT) {

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

}
