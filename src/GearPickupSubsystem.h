#pragma once

#include "CORERobotLib.h"
#include "WPILib.h"

#ifdef GEAR_PICKUP

using namespace CORE;

enum class GearPickupState{
	HOLDING,
	FEEDING,
	PICKUP,
	PLACING,
	PICKINGUP
};

class GearSubsystem : public CORESubsystem, public CORETask {
public:
    GearSubsystem();
    void robotInit() override;
    void teleopInit() override;
    void teleop() override;
    void teleopEnd() override;
    void placeGear();
    void pickupGear();
    void holdIn();
    void feed();
    void safePickup();
    void pickupIn();
    void pickupOut();
    void pickupOff();
    void setRoller(double val);
    void openFlap();
    void closeFlap();
    bool flapIsOpen();
    GearPickupState getState();

    void postLoopTask() override;
private:
    GearPickupState m_state = GearPickupState::HOLDING;
//    DoubleSolenoid m_leftManipulatorSolenoid, m_rightManipulatorSolenoid, m_leftFlapSolenoid, m_rightFlapSolenoid;
    DoubleSolenoid m_manipulatorForwardSolenoid, m_manipulatorReverseSolenoid, m_leftFlapSolenoid, m_rightFlapSolenoid;
//    Solenoid m_out;
//    Solenoid m_in;
    COREMotor m_rollerMotor;
    COREConstant<double> m_actuateTime, m_reverseRollerTime;
    CORETimer m_placeTimer;
    double oldIntakeButton = 0.0;
};

#endif
