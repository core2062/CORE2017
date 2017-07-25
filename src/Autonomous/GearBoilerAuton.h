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
	Node * m_approachPeg = nullptr;
	Node * m_waitForVision = nullptr;
	Node * m_driveOnPeg = nullptr;
	Node * m_driveToPeg = nullptr;
	Node * m_loadGearOnPeg = nullptr;
	Node * m_driveToBoiler = nullptr;
	Node * m_dumpBallsInBoiler = nullptr;
	Node * m_cross = nullptr;
	Node * m_driveCross = nullptr;

};

