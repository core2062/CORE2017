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
private:
    COREConstant<double> m_etherAValue, m_etherBValue, m_etherQuickTurnValue;
    COREMotor m_FRDrive, m_BRDrive, m_BLDrive, m_FLDrive;
    COREEtherDrive m_drive;
    DoubleSolenoid m_driveShifter;
};