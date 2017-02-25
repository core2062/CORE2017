#pragma once

#include <memory>

#include "CORERobotLib.h"
#include "WPILib.h"
using namespace CORE;

class TurnAngleAction : public COREAutonAction {
public:
	TurnAngleAction(double target, double tolerance, bool relative = false);
    void actionInit() override;
    COREAutonAction::actionStatus action() override;
    void actionEnd() override;
private:
    double m_angle, m_tolerance;
    bool m_setHighGear;
};
