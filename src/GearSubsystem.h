#pragma once

#include <CORERobotLib.h>
#include "WPILib.h"

using namespace CORE;

class GearSubsystem : public CORESubsystem {
public:
    GearSubsystem();
    void robotInit() override;
    void teleopInit() override;
    void teleop() override;
private:
    void openFlap();
    void closeFlap();
    bool flapIsOpen();
    DoubleSolenoid m_punchSolenoid;
};
