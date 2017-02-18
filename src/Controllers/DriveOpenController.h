#pragma once

#include "COREScheduler.h"

class DriveOpenController : public COREController{
public:
	DriveOpenController();
	void robotInitTask() override;
	void enabledLoop() override;
};
