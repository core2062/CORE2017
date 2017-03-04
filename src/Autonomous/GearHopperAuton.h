#pragma once
#include "Constants.h"
#include <memory>
#include "CORERobotLib.h"

using namespace CORE;

class GearHopperAuton : public COREAuton{
public:
	GearHopperAuton();
	void addNodes() override;

private:
	static Path * getPathForPeg(int startingPosition);
	static Path * backupFromPeg();
	static Path * driveToHopper();
	Node m_driveToPeg,
	m_loadGearOnPeg,
	m_backupFromPeg,
	m_driveToHopper,
	m_loadHopper;
};


