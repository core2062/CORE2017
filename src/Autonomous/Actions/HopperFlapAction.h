#pragma once
#include "CORERobotLib.h"
using namespace CORE;

class HopperFlapAction : public COREAutonAction {

public:
	HopperFlapAction();
	void actionInit() override;
    COREAutonAction::actionStatus action() override;
    void actionEnd() override;

};


