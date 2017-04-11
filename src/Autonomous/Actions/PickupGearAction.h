#pragma once

#include "CORERobotLib.h"
#include "WPILib.h"

using namespace CORE;

class PickupGearAction : public COREAutonAction {
public:
    PickupGearAction();
    void actionInit() override;
	COREAutonAction::actionStatus action() override;
	void actionEnd() override;
private:
	bool m_punchIsOut;
	Timer m_endTimer;

};
