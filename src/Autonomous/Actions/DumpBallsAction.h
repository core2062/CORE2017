#pragma once

#include "CORERobotLib.h"

class DumpBallsAction : public COREAutonAction {
public:
	DumpBallsAction(bool reset);
    void actionInit() override;
    void actionEnd() override;
    actionStatus action() override;
private:
    bool m_reset;
};
