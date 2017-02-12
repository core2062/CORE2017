#pragma once

#include <memory>

#include "CORERobotLib.h"
#include "Actions/DumpBalls.h"

class DumpBallsAuton : public COREAuton {
public:
	DumpBallsAuton(bool reset);
    void addNodes() override;
private:
    /*Node m_driveForward;*/
    DumpBalls m_dumpBalls;
};
