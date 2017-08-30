#pragma once

#include "COREFramework/COREScheduler.h"

class DriveOpenController : public COREController{
public:
	DriveOpenController();
	void robotInitTask() override;
	void enabledLoop() override;
//	void teleopInitTask() override;
	void autonEndTask() override;
	void teleopEndTask() override;
private:
};
