#pragma once

#include "CORERobotLib.h"
#include "WPILib.h"

using namespace CORE;

class PickupGearAction : public COREAutonAction {
public:
    PickupGearAction( bool up = false);
    void actionInit() override;
	COREAutonAction::actionStatus action() override;
	void actionEnd() override;
private:
	bool m_punchIsOut;
	bool m_up = false;
	Timer m_endTimer;

};
