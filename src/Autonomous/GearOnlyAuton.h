#pragma once
#include "Constants.h"
#include <memory>
#include "CORERobotLib.h"

using namespace CORE;

class GearOnlyAuton : public COREAuton{
public:
	GearOnlyAuton();
	void addNodes() override;
private:
	static Path * getPathFor(int startingPosition);
	Node m_driveToPeg, m_loadGearOnPeg;
};



