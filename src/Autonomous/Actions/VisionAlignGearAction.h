#pragma once

#include <memory>

#include "CORERobotLib.h"

using namespace CORE;

class VisionAlignGearAction : public COREAutonAction {
public:
	VisionAlignGearAction(double maxAccel, bool gradualStop, bool continuousUpdate);
	void actionInit() override;
	COREAutonAction::actionStatus action() override;
	void actionEnd() override;
private:
	double m_maxAccel = 25.0;
	bool m_gradualStop = true;
	bool m_continuousUpdate = true;
	Path m_calculatedPath;
};
