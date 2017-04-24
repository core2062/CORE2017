#pragma once

#include <memory>

#include "CORERobotLib.h"
#include "WPILib.h"
#include "WaypointFollower/Rotation2d.h"
using namespace CORE;

class TurnAngleAction : public COREAutonAction {
public:
	TurnAngleAction(Rotation2d target, double tolerance, int required = 1);
    void actionInit() override;
    COREAutonAction::actionStatus action() override;
    void actionEnd() override;
private:
    Rotation2d m_target;
    double m_tolerance;
    int m_seen = 0;
    int m_required;
};
