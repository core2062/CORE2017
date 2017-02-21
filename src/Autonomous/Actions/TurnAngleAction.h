#pragma once

#include <memory>

#include "CORERobotLib.h"
#include "WPILib.h"

class TurnAngleAction : public CORE::COREAutonAction {
public:
	TurnAngleAction(double target, double tolerance, bool relative = false);
    void actionInit() override;
    actionStatus action() override;
    void actionEnd() override;
private:
};
