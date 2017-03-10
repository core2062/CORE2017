#pragma once
#include "Constants.h"
#include <memory>
#include "CORERobotLib.h"

using namespace CORE;

class GearBoilerHopperAuton : public COREAuton{
public:
	GearBoilerHopperAuton(StartingPosition startingPosition);
	void addNodes() override;
private:
	static Path * getPathForPeg(StartingPosition startingPosition);
	static Path * backupFromPeg(StartingPosition startingPosition);
	static Path * driveToBoiler(StartingPosition startingPosition);
	static Path * backupFromBoiler(StartingPosition startingPosition);
	static Path * driveToHopper(StartingPosition startingPosition);

	Node * m_driveToPeg;
	Node * m_loadGearOnPeg;
	Node * m_backupFromPeg;
	Node * m_driveToBoiler;
	Node * m_dumpBallsInBoiler;
	Node * m_shimmyHopper;
	Node * m_backupFromBoiler;
	Node * m_driveToHopper;
	Node * m_loadHopper;


};


