#pragma once;

#include "Robot.h"
#include "CORERobotLib.h"

class TurnAngle : public COREAutonAction {
public:
	TurnAngle(double angle, double tolerance);
	void actionInit() override;
	actionStatus action() override;
	void actionEnd() override;
private:
	double m_angle;
	double m_tolerance;

};

