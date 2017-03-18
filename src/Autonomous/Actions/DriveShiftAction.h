#pragma once
#include "CORERobotLib.h"
#include "Constants.h"

using namespace CORE;
class DriveShiftAction : public COREAutonAction{
public:
	DriveShiftAction(GearPosition gearPosition);
	void actionInit() override;
	void actionEnd() override;
	COREAutonAction::actionStatus action() override;

private:
	GearPosition m_gearPosition;
};


