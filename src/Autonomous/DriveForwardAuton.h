#pragma once

#include <memory>

#include "CORERobotLib.h"
#include "Actions/DriveDistanceAction.h"
#include "Actions/DriveWaypointAction.h"
#include "Actions/GearFlapAction.h"

using namespace CORE;


class DriveForwardAuton : public COREAuton {
public:
    DriveForwardAuton(double speedInFraction, double distanceInFeet);
    void addNodes() override;
private:
    Node * m_setLowGearPosition = nullptr;
    Node * m_moveForwardToLine = nullptr;
    Node * m_spinInCircles = nullptr;

};

