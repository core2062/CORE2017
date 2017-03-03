#pragma once

#include "CORERobotLib.h"

#include <memory>

using namespace CORE;

class GearPunchAction : public COREAutonAction {

public:
	GearPunchAction();
    void actionInit() override;
    void actionEnd() override;
    COREAutonAction::actionStatus action() override;

private:

};


