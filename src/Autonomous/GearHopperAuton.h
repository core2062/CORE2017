#pragma once
#include "Constants.h"
#include <memory>
#include "CORERobotLib.h"

using namespace CORE;

class GearHopperAuton : public COREAuton{
public:
	GearHopperAuton(StartingPosition startingPosition);
	void addNodes() override;

private:
	static Path * getPathForPeg(StartingPosition startingPosition);
	static Path * backupFromPeg();
	static Path * driveToHopper();
	Node m_driveToPeg,
	m_loadGearOnPeg,
	m_backupFromPeg,
	m_driveToHopper,
	m_loadHopper;
};


