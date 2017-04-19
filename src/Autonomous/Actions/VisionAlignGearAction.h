#pragma once

#include <memory>

#include "CORERobotLib.h"

using namespace CORE;

class VisionAlignGearAction : public COREAutonAction {
public:
	VisionAlignGearAction();
	void actionInit() override;
	COREAutonAction::actionStatus action() override;
	void actionEnd() override;
private:

};
