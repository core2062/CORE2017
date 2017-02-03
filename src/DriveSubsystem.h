#pragma once

#include "CORERobotLib.h"

class DriveSubsystem : public CORESubsystem {
public:
    DriveSubsystem();
    void robotInit() override;
    void teleopInit() override;
    void teleop() override;
private:
    COREMotor m_FRDrive, m_BRDrive, m_BLDrive, m_FLDrive;
};
