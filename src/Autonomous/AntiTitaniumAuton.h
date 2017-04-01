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
	Node * m_setHighGearPosition = nullptr;
	Node * m_goToTheOppositeSideOfTheField = nullptr;

};


