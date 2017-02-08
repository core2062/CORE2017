#pragma once

#include <memory>

#include "CORERobotLib.h"

class DumpBallsAuton : public COREAuton {
public:
	DumpBallsAuton();
    void addNodes() override;
private:
    /*Node m_driveForward;*/
};
