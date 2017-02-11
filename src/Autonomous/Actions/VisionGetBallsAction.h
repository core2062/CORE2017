#pragma once

#include <memory>

#include "../../../CORERobotLib/CORERobotLib.h"

class VisionGetBallsAuton : public COREAuton {
public:
	VisionGetBallsAuton();
    void addNodes() override;
private:
    /*Node m_driveForward;*/
};
