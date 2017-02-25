#pragma once
#include "AHRS.h"
#include "CORERobotLib.h"
#include "WPILib.h"
#include "Controllers/DriveWaypointController.h"
#include "Controllers/DriveOpenController.h"
#include "Controllers/DriveGyroController.h"

enum DriveSide{LEFT = 1, RIGHT = 2, BOTH = 3};

using namespace CORE;

class DriveSubsystem : public COREVariableControlledSubsystem {
public:
    DriveSubsystem();
    void robotInit() override;
    void teleopInit() override;
//    void teleop() override;
    void initTalons();
    void setHighGear(bool highGear = true);
    void setLowGear(bool lowGear = true);
    bool getHighGear();
    bool getLowGear();
    void resetEncoders(DriveSide whichSide);
    double getDistanceInInches(DriveSide whichSide);
    void setMotorSpeed(double speedInFraction, DriveSide);
    void setMotorSpeed(double leftPercent, double rightPercent);
    void resetYaw();
    double getYaw();
    bool isTurning();
    void startTurning(double angle, double tolerance, bool relative = false);
    bool pathDone();
    bool checkPathFlag(std::string flag);
    void followPath(Path path, bool reversed = false, double maxAccel = 25.0, double tolerance = .25);
    CANTalon * getLeftMaster();
    CANTalon * getRightMaster();
    AHRS * getGyro();
    double getForwardPower();

	std::pair<double, double> getEncoderInches();
	std::pair<double, double> getEncoderSpeed();

	Rotation2d getGyroAngle();

    COREConstant<double>driveScrub;
    COREConstant<double>driveTurnProportional;
private:
    COREConstant<double> m_etherAValue, m_etherBValue, m_etherQuickTurnValue, m_ticksPerInch;
    COREMotor m_leftMaster, m_rightMaster, m_leftSlave, m_rightSlave;
    DoubleSolenoid m_leftDriveShifter, m_rightDriveShifter;
    bool m_highGear;
    shared_ptr<AHRS> m_gyro = 0;
    bool m_currentlyTurning;
    double m_currentYawTarget;
    double m_currentYawTolerance;
    COREConstant<double>m_turnPIDMultiplier;

    DriveOpenController m_driveTeleController;
    DriveGyroController m_driveGyroController;
    DriveWaypointController * m_driveWaypointController = 0;
};
