#pragma once

#include "CORERobotLib.h"
#include "WPILib.h"
#include "Controllers/DriveWaypointController.h"

class DriveWaypointAction : public CORE::COREAutonAction {
public:
	DriveWaypointAction(Path* path, bool reversed = false, double tolerance = .25, double maxAccel = 90.0, bool gradualStop = true);
    void actionInit() override;
    actionStatus action() override;
    void actionEnd() override;
private:
    Path* m_path;
    bool m_reversed = false;
    double m_tolerance = .25;
    double m_maxAccel = 25.0;
    bool m_gradualStop = true;
};
