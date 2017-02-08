#pragma once

#include <memory>

#include "../../../CORERobotLib/CORERobotLib.h"

class IntakeBallsAuton : public COREAuton {
public:
	IntakeBallsAuton();
    void addNodes() override;
private:
    /*Node m_driveForward;*/
};
