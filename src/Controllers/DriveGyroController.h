#pragma once

#include "COREScheduler.h"
#include "WaypointFollower/Rotation2d.h"

class DriveGyroController : public COREController{
public:
	DriveGyroController(double target = 0.0, double tolerance = 1.0, bool relative = false);
	void init(double target, double tolerance = 1.0, bool relative = false);
	void postLoopTask() override;
	void enabledLoop() override;
	bool isDone();
private:
	double getError();
	Rotation2d m_target;
	double m_tolerance = 0.0;
	double m_error = 0.0;
};
