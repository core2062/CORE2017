#pragma once

#include "CORERobotLib.h"

class LoadGearOntoPegAuton : public COREAutonAction {
public:
    LoadGearOntoPegAuton();
	actionStatus action() override;
private:

};
