#pragma once

#include "CORERobotLib.h"

class DriveSubsystem : public CORESubsystem {
public:
    DriveSubsystem();
    void robotInit() override;
    void teleopInit() override;
    void teleop() override;
private:
    COREMotor FRDrive, BRDrive, BLDrive, FLDrive;
};
