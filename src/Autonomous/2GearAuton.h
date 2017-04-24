#pragma once

#include "Constants.h"
#include <memory>
#include "CORERobotLib.h"

using namespace CORE;

class TwoGearAuton : public COREAuton{
public:
	TwoGearAuton();
	void addNodes();

private:

	Node * m_approachPeg = nullptr;
	Node * m_waitForVisionA = nullptr;
	Node * m_driveOnPegA = nullptr;
	Node * m_driveToPeg = nullptr;
	Node * m_dropA = nullptr;
	Node * m_driveToTurn = nullptr;
	Node * m_turnToPickup = nullptr;
	Node * m_driveToPickup = nullptr;
	Node * m_driveTowardsCenter = nullptr;
	Node * m_turnToPeg = nullptr;
	Node * m_driveBackToPeg = nullptr;
	Node * m_waitForVisionB = nullptr;
	Node * m_driveOnPegB = nullptr;
	Node * m_dropB = nullptr;

	Node * m_driveReverse = nullptr;

	Node * m_driveToBoiler = nullptr;
	Node * m_dumpBallsInBoiler = nullptr;

	Node * m_prepCrossA = nullptr;
	Node * m_prepCrossB = nullptr;
	Node * m_cross = nullptr;
};

