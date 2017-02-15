#pragma once

#include <memory>

#include "CORERobotLib.h"
#include "Actions/DriveDistance.h"

class DriveForwardAuton : public COREAuton {
public:
    DriveForwardAuton();
    void addNodes() override;
private:
    DriveDistance m_driveForward;
};
