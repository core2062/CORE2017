#pragma once

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
private:
    COREConstant<double> m_etherAValue, m_etherBValue, m_etherQuickTurnValue, m_ticksPerFoot;
    COREMotor m_FRDrive, m_BRDrive, m_BLDrive, m_FLDrive;
    COREEtherDrive m_drive;
    DoubleSolenoid m_leftDriveShifter, m_rightDriveShifter;
    bool m_highGear;
};
