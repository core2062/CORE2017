#pragma once

#include "CORERobotLib.h"

class ClimberSubsystem : public CORESubsystem {
public:
    ClimberSubsystem();
    void robotInit() override;
    void teleopInit() override;
    void teleop() override;
private:
    COREMotor LeftClimb, RightClimb;
};
