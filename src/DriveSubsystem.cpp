#include "DriveSubsystem.h"
#include "Robot.h"
#include "Math.h"

using namespace CORE;

DriveSubsystem::DriveSubsystem() : COREVariableControlledSubsystem("Drive Subsystem"),
								   driveTurnkP("Drive Turn P Value", .05),
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
								   m_leftBackModule(m_leftBackDrive, m_leftBackSteer),
								   m_rightBackModule(m_rightBackDrive, m_rightBackSteer),
								   m_rightFrontModule(m_rightFrontDrive, m_rightBackSteer),
								   m_leftFrontModule(m_leftFrontDrive, m_leftFrontSteer),
								   m_swerveDrive(27.7, 22.3, m_leftFrontModule, m_leftBackModule,
										   m_rightBackModule, m_rightFrontModule){
}

void DriveSubsystem::robotInit() {
    Robot->driverJoystick.registerButton(COREJoystick::LEFT_BUTTON);
    Robot->driverJoystick.registerButton(COREJoystick::RIGHT_BUTTON);
	Robot->driverJoystick.registerAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_Y);
	Robot->driverJoystick.registerAxis(CORE::COREJoystick::JoystickAxis::RIGHT_STICK_X);
    initTalons();
    SmartDashboard::PutNumber("P value", 0);
    SmartDashboard::PutNumber("I value", 0);
    SmartDashboard::PutNumber("D value", 0);

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
	//TODO not sure if this is right
	SmartDashboard::PutValue("P value", 0);
	SmartDashboard::PutValue("I value", 0);
	SmartDashboard::PutValue("D value", 0);
}


void DriveSubsystem::teleop(){
	initTalons();
	COREVariableControlledSubsystem::teleop();
}
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
/*
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
    return (m_leftDriveShifter.Get() == DoubleSolenoid::kForward);
}

bool DriveSubsystem::getLowGear() {
    return (m_leftDriveShifter.Get() == DoubleSolenoid::kReverse);
}
*/

void DriveSubsystem::resetEncoders(DriveSide whichSide){
	//Encoders only on front drive motors
	if (whichSide == DriveSide::BOTH || whichSide == DriveSide::RIGHT){
		m_rightFrontDrive.getCANTalon()->SetEncPosition(0);
		m_rightFrontDrive.getCANTalon()->SetPosition(0);
		m_rightBackSteer.getCANTalon()->SetPosition(0);
		m_rightBackSteer.getCANTalon()->SetEncPosition(0);
	}
	if (whichSide == DriveSide::BOTH || whichSide == DriveSide::LEFT){
		m_leftFrontSteer.getCANTalon()->SetEncPosition(0);
		m_leftFrontSteer.getCANTalon()->SetPosition(0);
		m_leftBackSteer.getCANTalon()->SetEncPosition(0);
		m_leftBackSteer.getCANTalon()->SetPosition(0);
	}
}
/*
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

*/

void DriveSubsystem::setMotors() {
	m_rightFrontModule->setAnglePID(SmartDashboard::GetNumber("P value", 0),
			SmartDashboard::GetNumber("I value", 0), SmartDashboard::GetNumber("D value", 0));
	m_rightBackModule->setAnglePID(SmartDashboard::GetNumber("P value", 0),
			SmartDashboard::GetNumber("I value", 0), SmartDashboard::GetNumber("D value", 0));
	m_leftFrontModule->setAnglePID(SmartDashboard::GetNumber("P value", 0),
			SmartDashboard::GetNumber("I value", 0), SmartDashboard::GetNumber("D value", 0));
	m_leftBackModule->setAnglePID(SmartDashboard::GetNumber("P value", 0),
			SmartDashboard::GetNumber("I value", 0), SmartDashboard::GetNumber("D value", 0));

    double y = Robot->driverJoystick.getAxis(COREJoystick::LEFT_STICK_Y);
    double x = Robot->driverJoystick.getAxis(COREJoystick::LEFT_STICK_X);
    double z = Robot->driverJoystick.getAxis(COREJoystick::RIGHT_STICK_X);
    double forward = y * cos(Robot->driveSubsystem.getYaw()) + x * sin(Robot->driveSubsystem.getYaw());
    double strafeRight = -y * sin(Robot->driveSubsystem.getYaw()) + x * cos(Robot->driveSubsystem.getYaw());

	m_swerveDrive->calculate(forward, strafeRight, z);

	m_rightFrontModule->drive(fabs(m_rightFrontDrive.getEncoder()->GetEncVel()),
					m_rightFrontModule->getAngle());
	m_rightBackModule->drive(fabs(m_rightBackDrive.getEncoder()->GetEncVel()),
					m_rightBackModule->getAngle());
	m_leftBackModule->drive(fabs(m_leftBackDrive.getEncoder()->GetEncVel()),
					m_leftBackModule->getAngle());
	m_leftFrontModule->drive(fabs(m_leftFrontDrive.getEncoder()->GetEncVel()),
					m_leftFrontModule->getAngle());

	m_swerveDrive->update();
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
	shared_ptr<CANTalon> leftFrontDrive = m_leftFrontDrive.getCANTalon();
	shared_ptr<CANTalon> rightFrontDrive = m_rightFrontDrive.getCANTalon();
	shared_ptr<CANTalon> leftBackDrive = m_leftBackDrive.getCANTalon();
	shared_ptr<CANTalon> rightBackDrive = m_rightBackDrive.getCANTalon();
	shared_ptr<CANTalon> leftFrontSteer = m_leftFrontSteer.getCANTalon();
	shared_ptr<CANTalon> rightFrontSteer = m_rightFrontSteer.getCANTalon();
	shared_ptr<CANTalon> leftBackSteer = m_leftBackSteer.getCANTalon();
	shared_ptr<CANTalon> rightBackSteer = m_rightBackSteer.getCANTalon();

	leftFrontDrive->SetStatusFrameRateMs(CANTalon::StatusFrameRateFeedback, 10);
	rightFrontDrive->SetStatusFrameRateMs(CANTalon::StatusFrameRateFeedback, 10);
	leftBackDrive->SetStatusFrameRateMs(CANTalon::StatusFrameRateFeedback, 10);
	rightBackDrive->SetStatusFrameRateMs(CANTalon::StatusFrameRateFeedback, 10);

	leftFrontDrive->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
	rightFrontDrive->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);

	m_leftFrontDrive.Set(0);
	m_rightFrontDrive.Set(0);
	m_leftBackDrive.Set(0);
	m_rightBackDrive.Set(0);
	m_leftFrontSteer.Set(0);
	m_rightFrontSteer.Set(0);
	m_leftBackSteer.Set(0);
	m_rightBackSteer.Set(0);

	leftFrontDrive->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Absolute);
	rightFrontDrive->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Absolute);
	leftBackDrive->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Absolute);
	rightBackDrive->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Absolute);
	leftFrontSteer->SetFeedbackDevice(CANTalon::FeedbackDevice::AnalogEncoder);
	rightFrontSteer->SetFeedbackDevice(CANTalon::FeedbackDevice::AnalogEncoder);
	leftBackSteer->SetFeedbackDevice(CANTalon::FeedbackDevice::AnalogEncoder);
	rightBackSteer->SetFeedbackDevice(CANTalon::FeedbackDevice::AnalogEncoder);

	leftFrontDrive->ConfigEncoderCodesPerRev(1024);
	rightFrontDrive->ConfigEncoderCodesPerRev(1024);
	leftBackDrive->ConfigEncoderCodesPerRev(1024);
	rightBackDrive->ConfigEncoderCodesPerRev(1024);
	leftFrontSteer->ConfigEncoderCodesPerRev(1024);
	rightFrontSteer->ConfigEncoderCodesPerRev(1024);
	leftBackSteer->ConfigEncoderCodesPerRev(1024);
	rightBackSteer->ConfigEncoderCodesPerRev(1024);
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
	return {m_leftMaster.getCANTalon()->GetPosition() * factor, m_rightMaster.getCANTalon()->GetPosition() * factor};
}

std::pair<double, double> DriveSubsystem::getEncoderSpeed() {
	double factor = TankKinematics::wheelDiameter.Get() * PI * .0166666666; //Multiply by 1/60 to get RPS from RPM
	return {m_leftMaster.getCANTalon()->GetSpeed() * factor, m_rightMaster.getCANTalon()->GetSpeed() * factor};
}
*/
Rotation2d DriveSubsystem::getGyroAngle() {
	double degrees = getYaw();
	return Rotation2d::fromDegrees(degrees);
}

CANTalon* DriveSubsystem::getLeftFrontSteer() {
	std::cout << "Drive Get Left Front Steer: " << std::endl;
	return m_leftFrontSteer.getCANTalon().get();
}

CANTalon* DriveSubsystem::getRightFrontSteer() {
	std::cout << "Drive Get Right Front Steer" << std::endl;
	return m_rightFrontSteer.getCANTalon().get();
}

CANTalon * DriveSubsystem::getLeftBackSteer() {
	std::cout << "Drive Get Left Back Steer" << std::endl;
	return m_rightBackSteer.getCANTalon().get();
}

CANTalon * DriveSubsystem::getRightBackSteer() {
	std::cout << "Drive Get Right Back Steer" << std::endl;
	return m_rightBackSteer.getCANTalon().get();
}

CANTalon * DriveSubsystem::getLeftFrontDrive() {
	std::cout << "Drive Get Left Front Drive" << std::endl;
	return m_leftFrontDrive.getCANTalon().get();
}

CANTalon * DriveSubsystem::getRightFrontDrive() {
	std::cout << "Drive Get Right Front Drive" << std::endl;
	return m_rightFrontDrive.getCANTalon().get();
}

CANTalon * DriveSubsystem::getLeftBackDrive() {
	std::cout << "Drive Get Left Back Drive" << std::endl;
	return m_leftBackDrive.getCANTalon().get();
}

CANTalon * DriveSubsystem::getRightBackDrive() {
	std::cout << "Drive Get Right Back Drive" << std::endl;
		return m_rightBackDrive.getCANTalon().get();
}

AHRS* DriveSubsystem::getGyro() {
	std::cout << "Drive Get Gyro" << std::endl;
	if(!m_gyro->IsConnected()) {
		CORELog::logError("NavX not connected!");
	}
	return m_gyro.get();
}
/*
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

void DriveSubsystem::setPos(Position2d pos) {
	if(m_driveWaypointController != nullptr){
		m_driveWaypointController->resetTracker(pos);
	}
}
*/
void DriveSubsystem::autonInitTask() {
	m_leftFrontSteer.getCANTalon()->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	m_rightFrontSteer.getCANTalon()->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	m_leftBackSteer.getCANTalon()->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	m_rightBackSteer.getCANTalon()->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	m_rightFrontDrive.getCANTalon()->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	m_leftFrontDrive.getCANTalon()->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	m_rightBackDrive.getCANTalon()->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	m_leftBackDrive.getCANTalon()->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
}
void DriveSubsystem::autonEndTask() {
	if(!CORERobot::IsCompetition()) { //This should make it easier to move robot manually when it is disabled
		m_leftFrontDrive.getCANTalon()->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
		m_rightFrontDrive.getCANTalon()->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
		m_leftBackDrive.getCANTalon()->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
		m_rightBackDrive.getCANTalon()->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
		m_leftFrontSteer.getCANTalon()->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
		m_rightFrontSteer.getCANTalon()->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
		m_leftBackSteer.getCANTalon()->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
		m_rightBackSteer.getCANTalon()->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
	}
}
void DriveSubsystem::teleopInitTask() {
	m_leftFrontSteer.getCANTalon()->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	m_rightFrontSteer.getCANTalon()->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	m_leftBackSteer.getCANTalon()->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	m_rightBackSteer.getCANTalon()->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	m_rightFrontDrive.getCANTalon()->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	m_leftFrontDrive.getCANTalon()->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	m_rightBackDrive.getCANTalon()->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	m_leftBackDrive.getCANTalon()->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
}
void DriveSubsystem::teleopEndTask() {
	if(!CORERobot::IsCompetition()) { //This should make it easier to move robot manually when it is disabled
		m_leftFrontDrive.getCANTalon()->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
		m_rightFrontDrive.getCANTalon()->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
		m_leftBackDrive.getCANTalon()->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
		m_rightBackDrive.getCANTalon()->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
		m_leftFrontSteer.getCANTalon()->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
		m_rightFrontSteer.getCANTalon()->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
		m_leftBackSteer.getCANTalon()->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
		m_rightBackSteer.getCANTalon()->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
	}
}
