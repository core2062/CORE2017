#pragma once

#include "COREScheduler.h"

class DriveOpenController : COREController{
public:
	DriveOpenController();
	void robotInitTask() override;
	void enabledLoop() override;
};
