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
	Node * m_driveToPeg;
	Node * m_loadGearOnPeg;
	Node * m_backupFromPeg;
	Node * m_driveToHopper;
	Node * m_loadHopper;
};


