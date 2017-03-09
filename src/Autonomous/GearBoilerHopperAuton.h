#pragma once
#include "Constants.h"
#include <memory>
#include "CORERobotLib.h"

using namespace CORE;

class GearBoilerHopper : public COREAuton{
public:
	GearBoilerHopper(StartingPosition startingPosition);
	void addNodes() override;
private:
	static Path * getPathForPeg(int startingPosition);
	static Path * backupFromPeg();
	static Path * driveToBoiler();
	static Path * backupFromBoiler();
	static Path * driveToHopper();

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


