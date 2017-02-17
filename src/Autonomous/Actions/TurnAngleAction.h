#pragma once

#include <memory>

#include "../../CORERobotLib/CORERobotLib.h"
#include "../../Robot.h"

class TurnAngleAction : public COREAutonAction {
public:
	TurnAngleAction(double target, double tolerance, bool relative = false);
    void actionInit() override;
    actionStatus action() override;
    void actionEnd() override;
private:
    /*Node m_driveForward;*/
};
