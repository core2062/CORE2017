#pragma once

#include "CORERobotLib.h"

class HopperSubsystem : public CORESubsystem{
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
    COREMotor liftMotor;
    DoubleSolenoid dumpFlap;
    COREPID liftPID;
    const double TOP_LIMIT = -1.0;
    const double BOTTOM_LIMIT = -1.0;//TODO: fill these data in
    const double RAISE_LIMIT = -1.0;
    const double LOWER_LIMIT = -1.0;

};
