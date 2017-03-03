#pragma once
#include "CORERobotLib.h"
using namespace CORE;

class ShimmyAction : public COREAutonAction {
public:
	ShimmyAction(double numberOfSeconds, double severityOfShimmy);
    void actionInit() override;
    void actionEnd() override;
    COREAutonAction::actionStatus action() override;
private:
	double m_numberOfSeconds;
	double m_severityOfShimmy;
	double m_shimmyPeriod;
	CORETimer m_shimmyTimer;

};


