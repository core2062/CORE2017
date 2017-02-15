#pragma once

#include <memory>

#include "CORERobotLib.h"

class VisionAlignGearAuton : public COREAuton {
public:
	VisionAlignGearAuton();
    void addNodes() override;
private:
    /*Node m_driveForward;*/
};
