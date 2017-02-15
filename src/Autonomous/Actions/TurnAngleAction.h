#pragma once

#include <memory>

#include "CORERobotLib.h"

class TurnAngleAction : public COREAutonAction {
public:
	TurnAngleAction(double angle, double tolerance);
	void actionInit() override;
	actionStatus action() override;
	void actionEnd() override;
private:
	double m_angle;
	double m_tolerance;

};
