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
	Node * m_setLowGearPosition = nullptr;
	Node * m_driveToPeg = nullptr;
	Node * m_loadGearOnPeg = nullptr;
	Node * m_reverseDrive = nullptr;
	Node * m_prepCrossA = nullptr;
	Node * m_prepCrossB = nullptr;
	Node * m_cross = nullptr;
};





