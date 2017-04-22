#pragma once
#include "Constants.h"
#include <memory>
#include "CORERobotLib.h"

using namespace CORE;

class AntiTitaniumAuton : public COREAuton{
public:
	AntiTitaniumAuton();
	void addNodes();

private:
	Node * m_setLowGear = nullptr;
	Node * m_approachPeg = nullptr;
	Node * m_waitForVision = nullptr;
	Node * m_driveOnPeg = nullptr;
	Node * m_loadGearOnPeg = nullptr;
	Node * m_reverseDrive = nullptr;
	Node * m_prepCrossA = nullptr;
	Node * m_prepCrossB = nullptr;
	Node * m_cross = nullptr;
};


