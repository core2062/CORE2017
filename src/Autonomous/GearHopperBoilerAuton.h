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
	static Path * backupFromPeg();
	static Path * driveToHopper();
	static Path * backupFromHopper();
	static Path * driveToBoiler();
	Node m_driveToPeg,
	m_loadGearOnPeg,
	m_backupFromPeg,
	m_driveToHopper,
	m_loadHopper,
	m_backupFromHopper,
	m_driveToBoiler,
	m_dumpBallsInBoiler,
	m_shimmyHopper,
	m_resetHopper;
	COREConstant<double> m_shimmyScale;
};


