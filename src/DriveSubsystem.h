#pragma once
#include "AHRS.h"
#include <src/COREDrive/COREEtherDrive.h>
#include "CORERobotLib.h"
#include "WPILib.h"

enum DriveSide{LEFT = 1, RIGHT = 2, BOTH = 3};

class DriveSubsystem : COREVariableControlledSubsystem {
public:
    DriveSubsystem();
    void robotInit() override;
    void teleopInit() override;
    //void teleop() override;	removed for now
    void initTalons();
    void setHighGear(bool highGear = true);
    void setLowGear(bool lowGear = true);
    bool getHighGear();
    bool getLowGear();
    void resetEncoders(DriveSide whichSide);
    double getDistanceInFeet(DriveSide whichSide);
    void setMotorSpeed(double speedInFraction, DriveSide);
    void setMotorSpeed(double leftPercent, double rightPercent);
    void resetYaw();
    double getYaw();
    bool isTurning();
    void startTurning(double angle, double tolerance);

	std::pair<double, double> getEncoderInches();
	std::pair<double, double> getEncoderSpeed();

	Rotation2d getGyroAngle();

    COREConstant<double>driveScrub;
private:
    COREConstant<double> m_etherAValue, m_etherBValue, m_etherQuickTurnValue, m_ticksPerInch;
    COREMotor m_leftMaster, m_rightMaster;
    CANTalon m_leftSlave, m_rightSlave;
    DoubleSolenoid m_leftDriveShifter, m_rightDriveShifter;
    bool m_highGear;
    AHRS * m_pGyro;
    bool m_currentlyTurning;
    double m_currentYawTarget;
    double m_currentYawTolerance;
    COREConstant<double>m_turnPIDMultiplier;
};
