#pragma once
#include "Constants.h"
#include <memory>
#include "CORERobotLib.h"


using namespace CORE;

class GearOnlyAuton : public COREAuton{
public:
	GearOnlyAuton(StartingPosition startingPosition);
	void addNodes() override;
private:
	static Path * getForwardPegPath(StartingPosition startingPosition);
	static Path * getReversePath(StartingPosition startingPosition);
	Node * m_driveToPeg = nullptr;
	Node * m_loadGearOnPeg = nullptr;
	Node * m_reverseDrive = nullptr;
};





