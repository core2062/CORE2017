#pragma once
#include "CORERobotLib.h"
using namespace CORE;

class ShimmyAction : public COREAutonAction {
public:
	ShimmyAction(double numberOfSeconds, double dir = 1.0);
    void actionInit() override;
    void actionEnd() override;
    COREAutonAction::actionStatus action() override;
private:
	double m_numberOfSeconds;
	double m_dir;
	CORETimer m_shimmyTimer;
};


