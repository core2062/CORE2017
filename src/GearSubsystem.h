#pragma once

#include "CORERobotLib.h"
#include "WPILib.h"

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
    COREMotor m_gearFlapMotor;
    COREConstant<double> m_gearFlapBottomPos, m_gearFlapTopPos;
    COREPID m_gearFlapPID;
};
