#pragma once
#include "CORERobotLib.h"
using namespace CORE;

class SetLiftPositionAction {
public:
	SetLiftPositionAction(bool setLiftTop, bool setLiftBottom);
	void actionInt() override;
    COREAutonAction::actionStatus action() override;
    void actionEnd() override;

private:
    double m_setLiftTop;
    double m_setLiftBottom;
};


