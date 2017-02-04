#pragma once

#include <src/COREDrive/COREEtherDrive.h>
#include "CORERobotLib.h"
#include "WPILib.h"

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
private:
    COREConstant<double> m_etherAValue, m_etherBValue, m_etherQuickTurnValue;
    COREMotor m_FRDrive, m_BRDrive, m_BLDrive, m_FLDrive;
    COREEtherDrive m_drive;
    DoubleSolenoid m_leftDriveShifter, m_rightDriveShifter;
    bool m_highGear;
};