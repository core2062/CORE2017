#include "DriveSubsystem.h"
#include "Robot.h"

using namespace CORE;

DriveSubsystem::DriveSubsystem() : COREVariableControlledSubsystem("Drive Subsystem"),
								   driveScrub("Drive Scrub", 0.15),
								   driveTurnProportional("Drive P Value", .3),
								   m_etherAValue("Ether A Value", .25),
                                   m_etherBValue("Ether B Value", .75),
								   m_etherQuickTurnValue("Ether Quick Turn Value", .5),
                                   m_ticksPerInch("Ticks Per Inch", 0),
								   m_leftMaster(FL_DRIVE_MOTOR_PORT),
								   m_rightMaster(FR_DRIVE_MOTOR_PORT),
								   m_leftSlave(BL_DRIVE_MOTOR_PORT),
								   m_rightSlave(BR_DRIVE_MOTOR_PORT),
                                   m_leftDriveShifter(LEFT_DRIVE_SHIFTER_PCM, LEFT_DRIVE_SHIFTER_HIGH_GEAR_PORT, LEFT_DRIVE_SHIFTER_LOW_GEAR_PORT),
                                   m_rightDriveShifter(RIGHT_DRIVE_SHIFTER_PCM, RIGHT_DRIVE_SHIFTER_HIGH_GEAR_PORT, RIGHT_DRIVE_SHIFTER_LOW_GEAR_PORT),
								   m_highGear(true),
								   m_currentlyTurning(false),
								   m_currentYawTarget(0),
								   m_currentYawTolerance(0),
								   m_turnPIDMultiplier("Turn PID Multiplier", 0.1) {
}

void DriveSubsystem::robotInit() {
    Robot->driverJoystick.registerButton(COREJoystick::LEFT_BUTTON);
    initTalons();

	try {
		m_gyro = make_shared<AHRS>(SerialPort::Port::kUSB, AHRS::SerialDataType::kProcessedData, 80);
		CORELog::logInfo("NavX Initialized!");
	} catch(std::exception & ex) {
		CORELog::logWarning("Couldn't find NavX!");
	}

}

void DriveSubsystem::teleopInit() {
	COREEtherDrive::setAB(m_etherAValue.Get(), m_etherBValue.Get());
	COREEtherDrive::setQuickturn(m_etherQuickTurnValue.Get());

}


//void DriveSubsystem::teleop(){
//	m_currentController->enabledLoop();
//}

/*
void DriveSubsystem::teleop() {
    double y = Robot::driverJoystick->getAxis(COREJoystick::LEFT_STICK_Y);
    double rot = Robot::driverJoystick->getAxis(COREJoystick::RIGHT_STICK_X);
    if(Robot::driverJoystick->getRisingEdge(COREJoystick::LEFT_BUTTON)) {
        if(m_highGear) {
            setLowGear();
        } else {
            setHighGear();
        }
    }
}
*/

void DriveSubsystem::setHighGear(bool highGear) {
    m_leftDriveShifter.Set(DoubleSolenoid::kForward);
    m_rightDriveShifter.Set(DoubleSolenoid::kForward);
    m_highGear = true;
}

void DriveSubsystem::setLowGear(bool lowGear) {
    m_leftDriveShifter.Set(DoubleSolenoid::kReverse);
    m_rightDriveShifter.Set(DoubleSolenoid::kReverse);
    m_highGear = false;
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
		m_rightMaster.getCANTalon()->SetEncPosition(0);
	}
	if (whichSide == DriveSide::BOTH || whichSide == DriveSide::LEFT){
		m_leftMaster.getCANTalon()->SetEncPosition(0);
	}
}

double DriveSubsystem::getDistanceInInches(DriveSide whichSide) {
	double accumulator = 0;
	//Encoders only on front drive motors
	if (whichSide == DriveSide::BOTH || whichSide == DriveSide::RIGHT){
		accumulator += abs(m_rightMaster.getCANTalon()->GetEncPosition());
	}
	if (whichSide == DriveSide::BOTH || whichSide == DriveSide::LEFT){
		accumulator += abs(m_leftMaster.getCANTalon()->GetEncPosition());
	}
	if (whichSide == DriveSide::BOTH){
		accumulator *= 0.5;
	}
	return accumulator / m_ticksPerInch.Get();
}

void DriveSubsystem::setMotorSpeed(double speedInFraction, DriveSide whichSide) {
	if (whichSide == DriveSide::BOTH || whichSide == DriveSide::RIGHT){
		m_rightMaster.Set(speedInFraction);
	}
	if (whichSide == DriveSide::BOTH || whichSide == DriveSide::LEFT){
		m_leftMaster.Set(speedInFraction);
	}
}

void DriveSubsystem::setMotorSpeed(double leftPercent, double rightPercent) {
	setMotorSpeed(leftPercent, DriveSide::LEFT);
	setMotorSpeed(rightPercent, DriveSide::RIGHT);
}

void DriveSubsystem::resetYaw() {
	m_gyro->ZeroYaw();

}

double DriveSubsystem::getYaw() {
	return (double) m_gyro->GetYaw();
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

void DriveSubsystem::initTalons() {
	shared_ptr<CANTalon> leftMaster = m_leftMaster.getCANTalon();
	shared_ptr<CANTalon> rightMaster = m_rightMaster.getCANTalon();
	shared_ptr<CANTalon> leftSlave = m_leftSlave.getCANTalon();
	shared_ptr<CANTalon> rightSlave = m_rightSlave.getCANTalon();

	leftMaster->SetStatusFrameRateMs(CANTalon::StatusFrameRateFeedback, 10);
	rightMaster->SetStatusFrameRateMs(CANTalon::StatusFrameRateFeedback, 10);

	leftMaster->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
	rightMaster->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);

	m_leftMaster.Set(0);
	m_leftSlave.setFollower(FL_DRIVE_MOTOR_PORT);

	m_rightMaster.Set(0);
	m_rightSlave.setFollower(FR_DRIVE_MOTOR_PORT);

	leftMaster->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
	leftMaster->SetSensorDirection(false);
	leftMaster->ConfigEncoderCodesPerRev(1024);
	leftMaster->SetInverted(false);
	leftSlave->SetInverted(false);

	rightMaster->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
	rightMaster->SetSensorDirection(true);
	rightMaster->ConfigEncoderCodesPerRev(1024);
	rightMaster->SetInverted(true);
	rightSlave->SetInverted(false);
}

std::pair<double, double> DriveSubsystem::getEncoderInches() {
	double factor = 4.0 * PI;
	return {m_leftMaster.getCANTalon()->GetPosition() * factor, m_rightMaster.getCANTalon()->GetPosition() * factor};
}

std::pair<double, double> DriveSubsystem::getEncoderSpeed() {
	double factor = 4.0 * PI * .0166666666; //Multiply by 1/60 to get RPS from RPM
	return {m_leftMaster.getCANTalon()->GetSpeed() * factor, m_rightMaster.getCANTalon()->GetSpeed() * factor};
}

Rotation2d DriveSubsystem::getGyroAngle() {
	double degrees = m_gyro->GetYaw();
	return Rotation2d::fromDegrees(degrees);
}

CANTalon* DriveSubsystem::getLeftMaster() {
	std::cout << "Drive Get Left master: " << m_leftMaster.getCANTalon().get() << std::endl;
	return m_leftMaster.getCANTalon().get();
}

CANTalon* DriveSubsystem::getRightMaster() {
	std::cout << "Drive Get Right Master" << std::endl;
	return m_rightMaster.getCANTalon().get();
}

AHRS* DriveSubsystem::getGyro() {
	std::cout << "Drive Get Gyro" << std::endl;
	return m_gyro.get();
}

double DriveSubsystem::getForwardPower() {
	double left = m_leftMaster.Get();
	double right = m_rightMaster.Get();
	double power  = 0;
	if(left > 0 || right > 0) {
		power = left + right;
		power*=.25;
		power = (power < 0)?0:power;
	}
	return power;
}
