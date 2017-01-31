#pragma once

#include "CORERobotLib.h"

class GearSubsystem : public CORESubsystem {
public:
    GearSubsystem();
    void robotInit() override;
    void teleopInit() override;
    void teleop() override;
private:
    DoubleSolenoid PunchSolenoid;
    DoubleSolenoid FlapSolenoid;
};
