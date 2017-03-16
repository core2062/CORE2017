#pragma once

#include "CORERobotLib.h"

using namespace CORE;

class DumpBallsAction : public COREAutonAction {
public:
	DumpBallsAction(double waitTime);
    void actionInit() override;
    void actionEnd() override;
    COREAutonAction::actionStatus action() override;
private:
    Timer m_waitTimer;
    double m_waitTime = 0.0;
};
