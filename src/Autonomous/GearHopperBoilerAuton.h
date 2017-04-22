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

	Node * m_setLowGear = nullptr;

	Node * m_approachPeg = nullptr;
	Node * m_waitForVision = nullptr;
	Node * m_driveOnPeg = nullptr;

	Node * m_driveToPeg = nullptr;
	Node * m_loadGearOnPeg = nullptr;

	Node * m_driveToHopperA = nullptr;
	Node * m_turnToHopper = nullptr;
	Node * m_driveToHopperB = nullptr;
	Node * m_loadHopper = nullptr;
	Node * m_driveToBoiler = nullptr;
	Node * m_dumpBallsInBoiler = nullptr;
};


