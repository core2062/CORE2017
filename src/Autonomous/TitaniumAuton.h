#pragma once
#include "Constants.h"
#include <memory>
#include "CORERobotLib.h"

using namespace CORE;

class TitaniumAuton : public COREAuton{
public:
	TitaniumAuton(StartingPosition startingPosition);
	void addNodes() override;
private:
	Node * m_setLowGear = nullptr;
	Node * m_driveToHopper = nullptr;
	Node * m_lowerLift = nullptr;
	Node * m_driveToBoiler = nullptr;
	Node * m_dumpBalls = nullptr;
};


