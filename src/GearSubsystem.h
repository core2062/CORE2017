#pragma once

#include "CORERobotLib.h"
#include "WPILib.h"

class GearSubsystem : public CORESubsystem {
public:
    GearSubsystem();
    void robotInit() override;
    void teleopInit() override;
    void teleop() override;
    void punchOut();
    void punchIn();
    bool checkPunchShouldClose();
    void openFlap();
    void closeFlap();
    bool flapIsOpen();
private:
    DoubleSolenoid m_punchSolenoid, m_leftFlapSolenoid, m_rightFlapSolenoid;
    COREConstant<double> m_punchTime;
    Timer m_punchTimer;
};
