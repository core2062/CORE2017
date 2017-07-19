#pragma once
#include "AHRS.h"
#include "CORERobotLib.h"
#include "WPILib.h"
#include "Controllers/DriveWaypointController.h"
#include "Controllers/DriveOpenController.h"
#include "Controllers/DriveGyroController.h"

enum class DriveSide{LEFT = 1, RIGHT = 2, BOTH = 3};

using namespace CORE;

class DriveSubsystem : public COREVariableControlledSubsystem, public CORETask {
public:
    DriveSubsystem();
    void robotInit() override;
    void teleopInit() override;
    void teleop() override;
    void initTalons();
    void resetEncoders(DriveSide whichSide);
    double getDistanceInInches(DriveSide whichSide);
    void setMotorSpeed(double speedInFraction, DriveSide);
    void setMotorSpeed(double leftPercent, double rightPercent);
    void hardResetYaw();
    void softResetYaw();
    double getYaw();
    bool isTurning();
    void startTurning(double angle, double tolerance, bool relative = false);
    bool pathDone();
    bool checkPathEvent(std::string event);
    void followPath(Path path, bool reversed = false, double maxAccel = 25.0, double tolerance = .25, bool gradualStop = true, double lookahead = 24.0);
    void setFrame(RobotFrame * frame);
    CANTalon * getLeftMaster();
    CANTalon * getRightMaster();
    AHRS * getGyro();

	std::pair<double, double> getEncoderInches();
	std::pair<double, double> getEncoderSpeed();

	Rotation2d getGyroAngle();

	void setPos(Position2d pos);

    COREConstant<double> driveTurnkP;

    void autonInitTask();
    void autonEndTask();
    void teleopInitTask();
    void teleopEndTask();
private:
    COREConstant<double> m_etherAValue, m_etherBValue, m_etherQuickTurnValue, m_ticksPerInch;
    COREMotor m_leftMaster, m_rightMaster, m_leftSlave, m_rightSlave;
    shared_ptr<AHRS> m_gyro = nullptr;
    bool m_currentlyTurning;
    double m_currentYawTarget;
    double m_currentYawTolerance;
    COREConstant<double> m_turnPIDMultiplier;

    DriveOpenController m_driveTeleController;
    DriveGyroController m_driveGyroController;
    DriveWaypointController * m_driveWaypointController = 0;
};
