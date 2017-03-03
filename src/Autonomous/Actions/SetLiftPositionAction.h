#pragma once
#include "CORERobotLib.h"
using namespace CORE;

class SetLiftPositionAction : public COREAutonAction {
public:
	SetLiftPositionAction(bool setLiftTop, bool setLiftBottom);
	void actionInit() override;
    COREAutonAction::actionStatus action() override;
    void actionEnd() override;

private:
    double m_setLiftTop;
    double m_setLiftBottom;
};


