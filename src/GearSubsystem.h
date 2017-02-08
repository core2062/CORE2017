#pragma once

#include "CORERobotLib.h"
#include "WPILIB.h"

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
    Servo m_leftGearFlapServo, m_rightGearFlap;
    COREConstant<double> m_gearFlapBottomPos, m_gearFlapTopPos;
    COREPID m_gearFlapPID;
};
