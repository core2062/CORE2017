#pragma once
#include "CORERobotLib.h"
using namespace CORE;

class GearFlapAction : public COREAutonAction {

public:
	GearFlapAction(ActuationType actuationType);
    void actionInit() override;
    void actionEnd() override;
    COREAutonAction::actionStatus action() override;
private:
    ActuationType m_actuationType;

};


