#pragma once

#include "Robot.h"
#include "CORERobotLib.h"

class IntakeBalls : public COREAutonAction {
public:
	IntakeBalls();
	void actionInit() override;
	actionStatus action() override;
	void actionEnd() override;
private:

};

