#include "DriveSubsystem.h"
#include "Robot.h"
#include "COREUtilities/COREMath.h"

using namespace CORE;

DriveSubsystem::DriveSubsystem() : driveTurnkP("Drive Turn P Value", .05),
								   m_etherAValue("Ether A Value", .6),
                                   m_etherBValue("Ether B Value", .4),
								   m_etherQuickTurnValue("Ether Quick Turn Value", 1.0),
                                   m_ticksPerInch("Ticks Per Inch", (4 * 3.1415) / 1024),
								   m_leftFrontSteer(LFS_DRIVE_MOTOR_PORT),
								   m_rightFrontSteer(RFS_DRIVE_MOTOR_PORT),
								   m_leftBackSteer(LBS_DRIVE_MOTOR_PORT),
								   m_rightBackSteer(RBS_DRIVE_MOTOR_PORT),
								   m_rightFrontDrive(RFD_DRIVE_MOTOR_PORT),
								   m_leftFrontDrive(LFD_DRIVE_MOTOR_PORT),
								   m_rightBackDrive(RBD_DRIVE_MOTOR_PORT),
								   m_leftBackDrive(LBD_DRIVE_MOTOR_PORT),
                                   m_leftDriveShifter(LEFT_DRIVE_SHIFTER_PCM, LEFT_DRIVE_SHIFTER_HIGH_GEAR_PORT, LEFT_DRIVE_SHIFTER_LOW_GEAR_PORT),
                                   m_rightDriveShifter(RIGHT_DRIVE_SHIFTER_PCM, RIGHT_DRIVE_SHIFTER_HIGH_GEAR_PORT, RIGHT_DRIVE_SHIFTER_LOW_GEAR_PORT),
								   m_highGear(true),
								   m_currentlyTurning(false),
								   m_currentYawTarget(0),
								   m_currentYawTolerance(0),
								   m_turnPIDMultiplier("Turn PID Multiplier", 0.1),
								   m_driveTeleController(),
								   m_driveGyroController(),
								   m_drivePIDValue_P("Drive PID P value", 0),
								   m_drivePIDValue_I("Drive PID I value", 0),
								   m_drivePIDValue_D("Drive PID D value", 0),
								   m_angleOffset("Angle offset", 0),
								   m_leftBackModule(&m_leftBackDrive, &m_leftBackSteer),
								   m_rightBackModule(&m_rightBackDrive, &m_rightBackSteer),
								   m_rightFrontModule(&m_rightFrontDrive, &m_rightBackSteer),
								   m_leftFrontModule(&m_leftFrontDrive, &m_leftFrontSteer),
								   m_swerveDrive(27.7, 22.3, m_leftFrontModule, m_leftBackModule,
										   m_rightBackModule, m_rightFrontModule){
}

void DriveSubsystem::robotInit() {
    Robot->driverJoystick.registerButton(COREJoystick::LEFT_BUTTON);
    Robot->driverJoystick.registerButton(COREJoystick::RIGHT_BUTTON);
	Robot->driverJoystick.registerAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_Y);
	Robot->driverJoystick.registerAxis(CORE::COREJoystick::JoystickAxis::RIGHT_STICK_X);
	Robot->driverJoystick.registerButton(CORE::COREJoystick::LEFT_TRIGGER);
    initTalons();

	try {
		m_gyro = make_shared<AHRS>(SerialPort::Port::kUSB, AHRS::SerialDataType::kProcessedData, 200);
		CORELog::logInfo("NavX Initialized!");
	} catch(std::exception & ex) {
		CORELog::logWarning("Couldn't find NavX!");
	}

		if(m_driveWaypointController == nullptr){
			m_driveWaypointController = new DriveWaypointController();
			m_driveWaypointController->init();
		}
}

void DriveSubsystem::teleopInit() {
	/*COREEtherDrive::setAB(m_etherAValue.Get(), m_etherBValue.Get());
	COREEtherDrive::setQuickturn(m_etherQuickTurnValue.Get());*/

	setController(&m_driveTeleController);
	m_driveTeleController.enable();
//	setController(&m_driveHybridController);
//	m_driveHybridController.enable();
	m_driveWaypointController->disable();

	if(!m_gyro->IsConnected()) {
		CORELog::logError("NavX not connected!");
	}
}


void DriveSubsystem::teleop(){
	initTalons();
	COREVariableControlledSubsystem::teleop();
}

void DriveSubsystem::resetEncoders(DriveSide whichSide){
	//Encoders only on front drive motors
	if (whichSide == DriveSide::BOTH || whichSide == DriveSide::RIGHT){
		m_rightFrontDrive.SetEncPosition(0);
		m_rightFrontDrive.SetPosition(0);
		m_rightBackSteer.SetPosition(0);
		m_rightBackSteer.SetEncPosition(0);
	}
	if (whichSide == DriveSide::BOTH || whichSide == DriveSide::LEFT){
		m_leftFrontSteer.SetEncPosition(0);
		m_leftFrontSteer.SetPosition(0);
		m_leftBackSteer.SetEncPosition(0);
		m_leftBackSteer.SetPosition(0);
	}
}
/*
double DriveSubsystem::getDistanceInInches(DriveSide whichSide) {
	double accumulator = 0;
	//Encoders only on front drive motors
	if (whichSide == DriveSide::BOTH || whichSide == DriveSide::RIGHT){
		accumulator += abs(m_rightMaster->GetEncPosition());
	}
	if (whichSide == DriveSide::BOTH || whichSide == DriveSide::LEFT){
		accumulator += abs(m_leftMaster->GetEncPosition());
	}
	if (whichSide == DriveSide::BOTH){
		accumulator *= 0.5;
	}
	return accumulator / m_ticksPerInch.Get();
}

*/

void DriveSubsystem::setMotors() {
	m_rightFrontModule.setAnglePID(m_drivePIDValue_P.Get(),
			m_drivePIDValue_I.Get(), m_drivePIDValue_D.Get());

	m_rightBackModule.setAnglePID(m_drivePIDValue_P.Get(),
			m_drivePIDValue_I.Get(), m_drivePIDValue_D.Get());

	m_leftFrontModule.setAnglePID(m_drivePIDValue_P.Get(),
			m_drivePIDValue_I.Get(), m_drivePIDValue_D.Get());

	m_leftBackModule.setAnglePID(m_drivePIDValue_P.Get(),
			m_drivePIDValue_I.Get(), m_drivePIDValue_D.Get());

    double y = -Robot->driverJoystick.getAxis(COREJoystick::LEFT_STICK_Y);

    double x = Robot->driverJoystick.getAxis(COREJoystick::LEFT_STICK_X);

    double z = Robot->driverJoystick.getAxis(COREJoystick::RIGHT_STICK_X);

    double forward = y * cos(Robot->driveSubsystem.getYaw() - m_angleOffset.Get()) +
    		x * sin(Robot->driveSubsystem.getYaw() - m_angleOffset.Get());
    SmartDashboard::PutNumber("Forward Value", forward);
    double strafeRight = -y * sin(Robot->driveSubsystem.getYaw() - m_angleOffset.Get()) +
    		x * cos(Robot->driveSubsystem.getYaw() - m_angleOffset.Get());
    SmartDashboard::PutNumber("Strafe Right Value", strafeRight);

    if (Robot->driverJoystick.getButton(COREJoystick::LEFT_TRIGGER)) {
    	m_swerveDrive.calculate(y, x, z);
    } else {
    	m_swerveDrive.calculate(forward, strafeRight, z);
    }

	SmartDashboard::PutNumber("Front Left Angle", (m_leftFrontModule.getAngle() - m_angleOffset.Get()));

	m_swerveDrive.update();

	SmartDashboard::PutNumber("Left Front Steer Analog", m_leftFrontSteer.GetAnalogInRaw());
	SmartDashboard::PutNumber("Right Front Steer Analog", m_leftBackSteer.GetAnalogInRaw());
	SmartDashboard::PutNumber("Left Back Steer Analog", m_rightBackSteer.GetAnalogInRaw());
	SmartDashboard::PutNumber("Right Back Steer Analog", m_rightFrontSteer.GetAnalogInRaw());
	SmartDashboard::PutNumber("Front Left Drive", m_rightFrontDrive.Get());
	SmartDashboard::PutNumber("Front Left Steer", m_rightFrontSteer.Get());
	SmartDashboard::PutNumber("Front Right Drive", m_leftFrontDrive.Get());
	SmartDashboard::PutNumber("Front Left Steer", m_leftFrontSteer.Get());
	SmartDashboard::PutNumber("Back Right Drive", m_rightBackDrive.Get());
	SmartDashboard::PutNumber("Back Right Steer", m_rightBackSteer.Get());
	SmartDashboard::PutNumber("Back Left Drive", m_leftBackDrive.Get());
	SmartDashboard::PutNumber("Back Left Steer", m_leftBackSteer.Get());


}

void DriveSubsystem::hardResetYaw() {
	m_gyro->ZeroYaw();
}

void DriveSubsystem::softResetYaw(){
	m_gyro->SetAngleAdjustment(-m_gyro->GetYaw());
}

double DriveSubsystem::getYaw() {
	return (double) m_gyro->GetAngle();
}

bool DriveSubsystem::isTurning() {
	return m_driveGyroController.isDone();
}

void DriveSubsystem::startTurning(double angle, double tolerance, bool relative) {
	m_driveGyroController.init(angle, tolerance, relative);
	setController(&m_driveGyroController);
	m_driveGyroController.enable();
}

bool DriveSubsystem::pathDone() {
	if(m_driveWaypointController){
		return m_driveWaypointController->isDone();
	}
	return true;
}

bool DriveSubsystem::checkPathEvent(std::string event) {
	if(m_driveWaypointController){
		return m_driveWaypointController->checkEvent(event);
	}
	return false;
}

void DriveSubsystem::followPath(Path path, bool reversed, double maxAccel,
		double tolerance, bool gradualStop, double lookahead) {
	if(!m_driveWaypointController){
		m_driveWaypointController = new DriveWaypointController();
		m_driveWaypointController->init();
	}
	m_driveWaypointController->startPath(path, reversed, maxAccel, tolerance, gradualStop, lookahead);
	m_driveWaypointController->enable();
}

void DriveSubsystem::setFrame(RobotFrame * frame){
	if(m_driveWaypointController){
		m_driveWaypointController->frame = frame;
	}
}

void DriveSubsystem::initTalons() {
    m_leftFrontDrive.SetStatusFrameRateMs(CANTalon::StatusFrameRateFeedback, 10);
	m_rightFrontDrive.SetStatusFrameRateMs(CANTalon::StatusFrameRateFeedback, 10);
	m_leftBackDrive.SetStatusFrameRateMs(CANTalon::StatusFrameRateFeedback, 10);
	m_rightBackDrive.SetStatusFrameRateMs(CANTalon::StatusFrameRateFeedback, 10);
	m_leftFrontSteer.SetStatusFrameRateMs(CANTalon::StatusFrameRateFeedback, 10);
	m_rightFrontSteer.SetStatusFrameRateMs(CANTalon::StatusFrameRateFeedback, 10);
	m_leftBackSteer.SetStatusFrameRateMs(CANTalon::StatusFrameRateFeedback, 10);
	m_rightBackSteer.SetStatusFrameRateMs(CANTalon::StatusFrameRateFeedback, 10);

	m_leftFrontDrive.SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
	m_rightFrontDrive.SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
	m_leftBackDrive.SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
	m_rightBackDrive.SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
	m_leftFrontSteer.SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
	m_rightFrontSteer.SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
	m_leftBackSteer.SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
	m_rightBackSteer.SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);

	m_leftFrontDrive.Set(0);
	m_rightFrontDrive.Set(0);
	m_leftBackDrive.Set(0);
	m_rightBackDrive.Set(0);
	m_leftFrontSteer.Set(0);
	m_rightFrontSteer.Set(0);
	m_leftBackSteer.Set(0);
	m_rightBackSteer.Set(0);

	m_leftFrontDrive.SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Absolute);
	m_rightFrontDrive.SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Absolute);
	m_leftBackDrive.SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Absolute);
	m_rightBackDrive.SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Absolute);
	m_leftFrontSteer.SetFeedbackDevice(CANTalon::FeedbackDevice::AnalogEncoder);
	m_rightFrontSteer.SetFeedbackDevice(CANTalon::FeedbackDevice::AnalogEncoder);
	m_leftBackSteer.SetFeedbackDevice(CANTalon::FeedbackDevice::AnalogEncoder);
	m_rightBackSteer.SetFeedbackDevice(CANTalon::FeedbackDevice::AnalogEncoder);

	m_leftFrontDrive.ConfigEncoderCodesPerRev(1024);
	m_rightFrontDrive.ConfigEncoderCodesPerRev(1024);
	m_leftBackDrive.ConfigEncoderCodesPerRev(1024);
	m_rightBackDrive.ConfigEncoderCodesPerRev(1024);
	m_leftFrontSteer.ConfigEncoderCodesPerRev(1024);
	m_rightFrontSteer.ConfigEncoderCodesPerRev(1024);
	m_leftBackSteer.ConfigEncoderCodesPerRev(1024);
	m_rightBackSteer.ConfigEncoderCodesPerRev(1024);
	/*leftFrontDrive->SetSensorDirection(false);
	leftMaster->SetInverted(false);
	leftSlave->SetInverted(false);

	rightMaster->SetSensorDirection(true);
	rightMaster->SetInverted(true);
	rightSlave->SetInverted(false);*/
}
/*
std::pair<double, double> DriveSubsystem::getEncoderInches() {
	double factor = TankKinematics::wheelDiameter.Get() * PI;
	return {m_leftMaster->GetPosition() * factor, m_rightMaster->GetPosition() * factor};
}

std::pair<double, double> DriveSubsystem::getEncoderSpeed() {
	double factor = TankKinematics::wheelDiameter.Get() * PI * .0166666666; //Multiply by 1/60 to get RPS from RPM
	return {m_leftMaster->GetSpeed() * factor, m_rightMaster->GetSpeed() * factor};
}
*/
Rotation2d DriveSubsystem::getGyroAngle() {
	double degrees = getYaw();
	return Rotation2d::fromDegrees(degrees);
}

CANTalon* DriveSubsystem::getLeftFrontSteer() {
	std::cout << "Drive Get Left Front Steer: " << std::endl;
	return &m_leftFrontSteer;
}

CANTalon* DriveSubsystem::getRightFrontSteer() {
	std::cout << "Drive Get Right Front Steer" << std::endl;
	return &m_rightFrontSteer;
}

CANTalon * DriveSubsystem::getLeftBackSteer() {
	std::cout << "Drive Get Left Back Steer" << std::endl;
	return &m_rightBackSteer;
}

CANTalon * DriveSubsystem::getRightBackSteer() {
	std::cout << "Drive Get Right Back Steer" << std::endl;
	return &m_rightBackSteer;
}

CANTalon * DriveSubsystem::getLeftFrontDrive() {
	std::cout << "Drive Get Left Front Drive" << std::endl;
	return &m_leftFrontDrive;
}

CANTalon * DriveSubsystem::getRightFrontDrive() {
	std::cout << "Drive Get Right Front Drive" << std::endl;
	return &m_rightFrontDrive;
}

CANTalon * DriveSubsystem::getLeftBackDrive() {
	std::cout << "Drive Get Left Back Drive" << std::endl;
	return &m_leftBackDrive;
}

CANTalon * DriveSubsystem::getRightBackDrive() {
	std::cout << "Drive Get Right Back Drive" << std::endl;
		return &m_rightBackDrive;
}

AHRS* DriveSubsystem::getGyro() {
	std::cout << "Drive Get Gyro" << std::endl;
	if(!m_gyro->IsConnected()) {
		CORELog::logError("NavX not connected!");
	}
	return m_gyro.get();
}

void DriveSubsystem::setPos(Position2d pos) {
	if(m_driveWaypointController != nullptr){
		m_driveWaypointController->resetTracker(pos);
	}
}

void DriveSubsystem::autonInitTask() {
	m_leftFrontSteer.ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	m_rightFrontSteer.ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	m_leftBackSteer.ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	m_rightBackSteer.ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	m_rightFrontDrive.ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	m_leftFrontDrive.ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	m_rightBackDrive.ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	m_leftBackDrive.ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
}
void DriveSubsystem::autonEndTask() {
	if(!COREDriverstation::isCompetition()) { //This should make it easier to move robot manually when it is disabled
		m_leftFrontDrive.ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
		m_rightFrontDrive.ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
		m_leftBackDrive.ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
		m_rightBackDrive.ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
		m_leftFrontSteer.ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
		m_rightFrontSteer.ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
		m_leftBackSteer.ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
		m_rightBackSteer.ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
	}
}
void DriveSubsystem::teleopInitTask() {
	m_leftFrontSteer.ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	m_rightFrontSteer.ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	m_leftBackSteer.ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	m_rightBackSteer.ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	m_rightFrontDrive.ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	m_leftFrontDrive.ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	m_rightBackDrive.ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	m_leftBackDrive.ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
}
void DriveSubsystem::teleopEndTask() {
	if(!COREDriverstation::isCompetition()) { //This should make it easier to move robot manually when it is disabled
		m_leftFrontDrive.ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
		m_rightFrontDrive.ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
		m_leftBackDrive.ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
		m_rightBackDrive.ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
		m_leftFrontSteer.ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
		m_rightFrontSteer.ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
		m_leftBackSteer.ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
		m_rightBackSteer.ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
	}
}
