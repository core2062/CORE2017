#pragma once
#include "Constants.h"
#include <memory>
#include "CORERobotLib.h"
#include "GearOnlyAuton.h"

using namespace CORE;

class GearBoilerAuton : public COREAuton{
public:
	GearBoilerAuton(StartingPosition startingPosition);
	void addNodes();

private:
	static Path * getPathForBoiler(StartingPosition startingPosition);
	static Path * getForwardPath(StartingPosition startingPosition);
	Node * m_driveToPeg;
	Node * m_loadGearOnPeg;
	Node * m_driveToBoiler;
	Node * m_dumpBallsInBoiler;
	Node * m_shimmyHopper;
	Node * m_resetHopper;
};

