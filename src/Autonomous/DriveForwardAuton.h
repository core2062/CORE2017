#pragma once

#include <memory>

#include "CORERobotLib.h"
#include "Actions/DriveDistance.h"
#include "Robot.h"

class DriveForwardAuton : public COREAuton {
public:
    DriveForwardAuton(double speedInFraction, double distanceInFeet);
    void addNodes() override;
private:
    DriveDistance m_driveForward;
};
