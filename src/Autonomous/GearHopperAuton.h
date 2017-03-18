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
	static Path * backupFromPeg(StartingPosition startingPosition);
	static Path * driveToHopper(StartingPosition startingPosition);
	Node * m_setLowGearPosition = nullptr;
	Node * m_driveToPeg = nullptr;
	Node * m_loadGearOnPeg = nullptr;
	Node * m_backupFromPeg = nullptr;
	Node * m_driveToHopper = nullptr;
	Node * m_loadHopper = nullptr;
};


