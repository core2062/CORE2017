#pragma once

#include <memory>

#include "CORERobotLib.h"

class DriveForwardAuton : public COREAuton {
public:
    DriveForwardAuton();
    void addNodes() override;
private:
    /*Node m_driveForward;*/
};
