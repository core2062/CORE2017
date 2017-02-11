#pragma once
#include "Robot.h"
#include "CORERobotLib.h"
#include "HopperSubsystem.h"

class DumpBalls : public COREAutonAction {
public:
	DumpBalls(bool reset);
	void actionInit() override;
	actionStatus action() override;
	void actionEnd() override;
private:
	bool m_reset;
};


