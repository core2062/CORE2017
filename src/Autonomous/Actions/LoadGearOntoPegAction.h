#pragma once

#include <memory>

#include "../../../CORERobotLib/CORERobotLib.h"

class LoadGearOntoPegAuton : public COREAuton {
public:
	LoadGearOntoPegAuton();
    void addNodes() override;
private:
    /*Node m_driveForward;*/
};
