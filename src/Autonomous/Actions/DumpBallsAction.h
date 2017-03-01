#pragma once

#include "CORERobotLib.h"

using namespace CORE;

class DumpBallsAction : public COREAutonAction {
public:
	DumpBallsAction(bool reset);
    void actionInit() override;
    void actionEnd() override;
    COREAutonAction::actionStatus action() override;
private:
    bool m_reset;
};
