#include "DriveSubsystem.h"
#include "Robot.h"

DriveSubsystem::DriveSubsystem() : CORESubsystem("Drive Subsystem"), FRDrive(FR_DRIVE_MOTOR_PORT),
									BRDrive(BR_DRIVE_MOTOR_PORT), BLDrive(BL_DRIVE_MOTOR_PORT), FLDrive(FL_DRIVE_MOTOR_PORT ) {

}

void DriveSubsystem::robotInit() {

}

void DriveSubsystem::teleopInit() {

}

void DriveSubsystem::teleop() {

}
