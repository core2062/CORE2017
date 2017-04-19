#pragma once

#include <memory>

#include "CORERobotLib.h"
#include "WPILib.h"
#include "WaypointFollower/Rotation2d.h"
using namespace CORE;

class TurnAngleAction : public COREAutonAction {
public:
	TurnAngleAction(Rotation2d target, double tolerance);
    void actionInit() override;
    COREAutonAction::actionStatus action() override;
    void actionEnd() override;
private:
    Rotation2d m_target;
    double m_tolerance;
};
