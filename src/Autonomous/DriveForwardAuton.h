#pragma once

#include <memory>

#include "CORERobotLib.h"
#include "Actions/DriveDistanceAction.h"
#include "Actions/DriveWaypointAction.h"
#include "Actions/GearFlapAction.h"

using namespace CORE;


class DriveForwardAuton : public COREAuton {
public:
    DriveForwardAuton();
    void addNodes() override;
private:
    Node m_moveForwardToLine, m_spinInCircles;
    COREConstant<double> m_speedInFraction, m_distanceInFeet;

};

