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
	static Path * getPathFor(StartingPosition startingPosition);
	Node m_driveToPeg, m_loadGearOnPeg, m_reverseDrive;
};





