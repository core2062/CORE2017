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
	Node * m_driveToPeg = nullptr;
	Node * m_loadGearOnPeg = nullptr;
	Node * m_driveToBoiler = nullptr;
	Node * m_dumpBallsInBoiler = nullptr;
	Node * m_shimmyHopper = nullptr;
	Node * m_resetHopper = nullptr;
};

