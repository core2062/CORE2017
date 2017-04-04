#ifdef GEAR_PICKUP
#pragma once

#include "CORERobotLib.h"
#include "WPILib.h"


using namespace CORE;

enum class GearPickupState{
	HOLDING,
	FEEDING,
	PICKUP,
	PLACING
};

class GearSubsystem : public CORESubsystem, public CORETask {
public:
    GearSubsystem();
    void robotInit() override;
    void teleopInit() override;
    void teleop() override;
    void placeGear();
    void pickupGear();
    void holdIn();
    void feed();
    void pickupIn();
    void pickupOut();
    void setRoller(double val);
    void openFlap();
    void closeFlap();
    bool flapIsOpen();

    void postLoopTask() override;
private:
    GearPickupState m_state = GearPickupState::HOLDING;
    DoubleSolenoid m_leftManipulatorSolenoid, m_rightManipulatorSolenoid, m_leftFlapSolenoid, m_rightFlapSolenoid;
    COREMotor m_rollerMotor;
    COREConstant<double> m_placeTime, m_reverseRollerTime;
    CORETimer m_placeTimer;
};

#endif
