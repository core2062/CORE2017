#include "DriveSubsystem.h"
#include "Robot.h"

DriveSubsystem::DriveSubsystem() : CORESubsystem("Drive Subsystem"),
								   m_etherAValue("Ether A Value", 1),
                                   m_etherBValue("Ether B Value", 1),
								   m_etherQuickTurnValue("Ether Quick Turn Value", 2),
                                   m_ticksPerInch("Ticks Per Inch", 10000),
								   m_FRDrive(FR_DRIVE_MOTOR_PORT), m_BRDrive(BR_DRIVE_MOTOR_PORT),
								   m_BLDrive(BL_DRIVE_MOTOR_PORT), m_FLDrive(FL_DRIVE_MOTOR_PORT),
                                   m_drive(&m_BLDrive, &m_FLDrive, &m_BRDrive, &m_FRDrive, m_etherAValue.Get(),
                                           m_etherBValue.Get(),m_etherQuickTurnValue.Get()),
                                   m_leftDriveShifter(LEFT_DRIVE_SHIFTER_HIGH_GEAR_PORT, LEFT_DRIVE_SHIFTER_LOW_GEAR_PORT),
                                   m_rightDriveShifter(RIGHT_DRIVE_SHIFTER_HIGH_GEAR_PORT, RIGHT_DRIVE_SHIFTER_LOW_GEAR_PORT),
								   m_highGear(true),
								   m_currentlyTurning(false),
								   m_currentYawTarget(0),
								   m_currentYawTolerance(0),
								   m_turnPIDMultiplier("Turn PID Multiplier", 0.1)
								   {
	try{
		//m_pGyro = new AHRS(SerialPort::Port::kMXP);
	}
	catch(std::exception & ex){
		std::cout<<"Couldn't find NavX"<<std::endl;
	}
}

void DriveSubsystem::robotInit() {
	m_FRDrive.setReversed(false);
	m_BRDrive.setReversed(false);
	m_BLDrive.setReversed(false);
	m_FLDrive.setReversed(false);
    Robot::driverJoystick->registerButton(COREJoystick::LEFT_BUTTON);
}

void DriveSubsystem::teleopInit() {

}

void DriveSubsystem::teleop() {
    double y = Robot::driverJoystick->getAxis(COREJoystick::LEFT_STICK_Y);
    double rot = Robot::driverJoystick->getAxis(COREJoystick::RIGHT_STICK_X);
    m_drive.cartesian(0, y, rot);
    if(Robot::driverJoystick->getRisingEdge(COREJoystick::LEFT_BUTTON)) {
        if(m_highGear) {
            setLowGear();
        } else {
            setHighGear();
        }
    }
}

void DriveSubsystem::setHighGear(bool highGear) {
    m_leftDriveShifter.Set(DoubleSolenoid::kForward);
    m_rightDriveShifter.Set(DoubleSolenoid::kForward);
}

void DriveSubsystem::setLowGear(bool lowGear) {
    m_leftDriveShifter.Set(DoubleSolenoid::kReverse);
    m_rightDriveShifter.Set(DoubleSolenoid::kReverse);
}

bool DriveSubsystem::getHighGear() {
    return m_highGear;
}

bool DriveSubsystem::getLowGear() {
    return !m_highGear;
}

void DriveSubsystem::resetEncoders(DriveSide whichSide){
	//Encoders only on front drive motors
	if (whichSide == DriveSide::BOTH || whichSide == DriveSide::RIGHT){
		m_FRDrive.CANTalonController->SetEncPosition(0);
	}if (whichSide == DriveSide::BOTH || whichSide == DriveSide::LEFT){
		m_FLDrive.CANTalonController->SetEncPosition(0);
	}
}

double DriveSubsystem::getDistanceInFeet(DriveSide whichSide){
	double accumulator = 0;
	//Encoders only on front drive motors
	if (whichSide == DriveSide::BOTH || whichSide == DriveSide::RIGHT){
		accumulator += abs(m_FRDrive.CANTalonController->GetEncPosition());
	}
	if (whichSide == DriveSide::BOTH || whichSide == DriveSide::LEFT){
		accumulator += abs(m_FLDrive.CANTalonController->GetEncPosition());
	}
	if (whichSide == DriveSide::BOTH){
		accumulator *= 0.5;
	}
	return accumulator / m_ticksPerInch.Get();
}

void DriveSubsystem::setMotorSpeed(double speedInFraction, DriveSide whichSide){
	if (whichSide == DriveSide::BOTH || whichSide == DriveSide::RIGHT){
		m_FRDrive.Set(speedInFraction);
		m_BRDrive.Set(speedInFraction);
	}
	if (whichSide == DriveSide::BOTH || whichSide == DriveSide::LEFT){
		m_FLDrive.Set(speedInFraction);
		m_BLDrive.Set(speedInFraction);
	}
}

void DriveSubsystem::resetYaw() {
	m_pGyro->ZeroYaw();

}

double DriveSubsystem::getYaw() {
	return (double) m_pGyro->GetYaw();
}

bool DriveSubsystem::isTurning() {
	//Determine error from current yaw and target yaw
	//If error is greater than tolerance
	//SetPID Controller value according to the error signal, and return true
	//Otherwise drive motor controller set drive motors to zero, and return false
	return m_currentlyTurning;
}

void DriveSubsystem::startTurning(double angle, double tolerance) {
	//TODO:: Fill this in
	//If angle is more than the tolerance
	//Figure out the right direction
	//Set motors in opposite directions, to turn the right way

}
