#pragma once

#include <memory>

#include "CORERobotLib.h"

using namespace CORE;

class TurnAngleAction : public COREAutonAction {
public:
	TurnAngleAction(double angle, double tolerance, bool setHighGear);
	void actionInit() override;
	COREAutonAction::actionStatus action() override;
	void actionEnd() override;

private:
	double m_angle;
	double m_tolerance;
	bool m_setHighGear;
};
