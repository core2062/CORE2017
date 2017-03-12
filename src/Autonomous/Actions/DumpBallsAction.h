#pragma once

#include "CORERobotLib.h"

using namespace CORE;

class DumpBallsAction : public COREAutonAction {
public:
	DumpBallsAction(double dumpFlapTime);
    void actionInit() override;
    void actionEnd() override;
    COREAutonAction::actionStatus action() override;
private:
    CORETimer m_timer;
    double m_dumpFlapTime;
};
