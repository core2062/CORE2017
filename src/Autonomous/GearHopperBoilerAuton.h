#pragma once
#include "Constants.h"
#include <memory>
#include "CORERobotLib.h"

using namespace CORE;


class GearHopperBoilerAuton : public COREAuton{
public:
	GearHopperBoilerAuton();
	void addNodes() override;

private:
	static Path * getPathForPeg(StartingPosition startingPosition);
	static Path * backupFromPeg(StartingPosition startingPosition);
	static Path * driveToHopper(StartingPosition startingPosition);
	static Path * backupFromHopper(StartingPosition startingPosition);
	static Path * driveToBoiler(StartingPosition startingPosition);

	Node * m_setLowGearPosition = nullptr;
	Node * m_driveToPeg = nullptr;
	Node * m_loadGearOnPeg = nullptr;
	Node * m_backupFromPeg = nullptr;
	Node * m_driveToHopper = nullptr;
	Node * m_loadHopper = nullptr;
	Node * m_backupFromHopper = nullptr;
	Node * m_driveToBoiler = nullptr;
	Node * m_dumpBallsInBoiler = nullptr;
	Node * m_shimmyHopper = nullptr;
	Node * m_resetHopper = nullptr;
	COREConstant<double> m_shimmyScale;
};


