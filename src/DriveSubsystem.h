#pragma once
#include <AHRS.h>
#include <src/COREDrive/COREEtherDrive.h>
#include "CORERobotLib.h"
#include "WPILib.h"

enum DriveSide{LEFT = 1, RIGHT = 2, BOTH = 3};

class DriveSubsystem : CORESubsystem {
public:
    DriveSubsystem();
    void robotInit() override;
    void teleopInit() override;
    void teleop() override;
    void setHighGear(bool highGear = true);
    void setLowGear(bool lowGear = true);
    bool getHighGear();
    bool getLowGear();
    void resetEncoders(DriveSide whichSide);
    double getDistanceInFeet(DriveSide whichSide);
    void setMotorSpeed(double speedInFraction, DriveSide);
    void resetYaw();
    double getYaw();
    bool isTurning();
    void startTurning(double angle, double tolerance);

private:
    COREConstant<double> m_etherAValue, m_etherBValue, m_etherQuickTurnValue, m_ticksPerInch;
    COREMotor m_FRDrive, m_BRDrive, m_BLDrive, m_FLDrive;
    COREEtherDrive m_drive;
    DoubleSolenoid m_leftDriveShifter, m_rightDriveShifter;
    bool m_highGear;
    AHRS * m_pGyro;
    bool m_currentlyTurning;
    double m_currentYawTarget;
    double m_currentYawTolerance;
    COREConstant<double>m_turnPIDMultiplier;
};
