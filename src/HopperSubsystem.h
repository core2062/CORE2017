#pragma once

#include "CORERobotLib.h"

class HopperSubsystem : public CORESubsystem {
public:
    HopperSubsystem();
    void robotInit() override;
    void teleopInit() override;
    void teleop() override;

    void setLiftTop();
    void setLiftBottom();
    void openFlap();
    void closeFlap();
    bool flapIsOpen();


private:
    COREMotor m_liftMotor;
    COREMotor m_dumpFlapMotor;
    COREPID m_liftPID;
    COREConstant<double> m_bottomPos, m_topPos, m_raiseVel, m_lowerVel;
};

