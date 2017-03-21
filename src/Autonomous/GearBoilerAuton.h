#pragma once
#include "Constants.h"
#include <memory>
#include "CORERobotLib.h"
#include "GearOnlyAuton.h"

using namespace CORE;

class GearBoilerAuton : public COREAuton{
public:
	GearBoilerAuton();
	void addNodes();

private:
	Node * m_setLowGearPosition = nullptr;
	Node * m_driveToPeg = nullptr;
	Node * m_loadGearOnPeg = nullptr;
	Node * m_driveToBoiler = nullptr;
	Node * m_dumpBallsInBoiler = nullptr;
	Node * m_shimmyHopper = nullptr;
	Node * m_resetHopper = nullptr;
	Node * m_goHigh = nullptr;
	Node * m_cross = nullptr;
	Node * m_driveCross = nullptr;

};

