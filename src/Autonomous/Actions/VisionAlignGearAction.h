#pragma once

#include <memory>

#include "CORERobotLib.h"

using namespace CORE;

class VisionAlignGearAuton : public COREAutonAction {
public:
	VisionAlignGearAuton();
	void actionInit() override;
	COREAutonAction::actionStatus action() override;
	void actionEnd() override;
private:

};
