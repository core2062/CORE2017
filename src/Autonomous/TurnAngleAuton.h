#pragma once

#include <memory>

#include "../../../CORERobotLib/CORERobotLib.h"

class TurnAngleAuton : public COREAuton {
public:
	TurnAngleAuton();
    void addNodes() override;
private:
    /*Node m_driveForward;*/
};
