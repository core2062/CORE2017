#pragma once
#include "Constants.h"
#include <memory>
#include "CORERobotLib.h"

using namespace CORE;

class GearBoilerHopper : public COREAuton{
public:
	GearBoilerHopper();
	void addNodes() override;
private:
	static Path * getPathForPeg(int startingPosition);
	static Path * backupFromPeg();
	static Path * driveToBoiler();
	static Path * backupFromBoiler();
	static Path * driveToHopper();

	//Node m_driveToPeg,
	//m_loadGearOnPeg,
	//m_backupFromPeg,
	//m_driveToBoiler,
	//m_dumpBallsInBoiler,
	//m_shimmyHopper;

	//Add the rest of the nodes in the .h and .cpp
};


