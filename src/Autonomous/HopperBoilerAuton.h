#pragma once
#include "Constants.h"
#include <memory>
#include "CORERobotLib.h"


using namespace CORE;

class HopperBoilerAuton : public COREAuton{
public:
	HopperBoilerAuton(StartingPosition startingPosition);
	void addNodes() override;

private:
	static Path * getWallToHopperPath(StartingPosition startingPosition);
	static Path * backupFromHopper(StartingPosition startingPosition);
	static Path * getHopperToBoilerPath(StartingPosition startingPosition);

	Node * m_setLowGearPosition = nullptr;
	Node * m_driveToHopper = nullptr;
	Node * m_loadHopper = nullptr;
	Node * m_driveToBoiler = nullptr;
	Node * m_dumpBallsInBoiler = nullptr;
	Node * m_shimmyHopper = nullptr;
	Node * m_resetHopper = nullptr;
	Node * m_driveToPeg = nullptr;
	COREConstant<double> m_shimmyScale;

};


