#pragma once

#include "COREScheduler.h"
#include "WaypointFollower/WaypointFollower.h"

class DriveWaypointController : public COREController{
private:
	Path m_path;
	TankTracker m_tracker;
	AdaptivePursuit m_pursuit;

public:
	DriveWaypointController();
	void preLoopTask() override;
	void postLoopTask() override;
	void enabledLoop() override;
	void enable() override;
	void disable() override;

	void init();
	void startPath(Path path, bool reversed = false, double maxAccel = 25.0, double tolerance = .25);
	void resetTracker(Position2d initialPos);
	bool isDone();
	bool checkFlag(std::string flag);
	void updatePathFollower();

};
