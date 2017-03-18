#pragma once;
#include "CORERobotLib.h"
#include "Constants.h"

using namespace CORE;
class DriveForwardWithoutPathAction : public COREAutonAction {
public:
	DriveForwardWithoutPathAction(GearPosition gearPosition);
	void actionInit();
	void actionEnd();
	COREAutonAction::actionStatus action();

private:
	GearPosition m_gearPosition;
};

