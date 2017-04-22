#pragma once

#pragma once

#include "COREScheduler.h"
#include "DriveWaypointController.h"

class DriveHybridController : public COREController{
public:
	DriveHybridController();
	void robotInitTask() override;
	void enabledLoop() override;

private:
	bool m_hybrid = false;
	AdaptivePursuit * m_pursuit = nullptr;
	RobotFrame * m_frame = nullptr;
	Timer m_visionTimer;

};
