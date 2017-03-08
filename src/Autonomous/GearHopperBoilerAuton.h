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
	Node * m_driveToPeg;
	Node * m_loadGearOnPeg;
	Node * m_backupFromPeg;
	Node * m_driveToHopper;
	Node * m_loadHopper;
	Node * m_backupFromHopper;
	Node * m_driveToBoiler;
	Node * m_dumpBallsInBoiler;
	Node * m_shimmyHopper;
	Node * m_resetHopper;
	COREConstant<double> m_shimmyScale;
};


