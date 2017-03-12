#pragma once
#include "Constants.h"
#include <memory>
#include "CORERobotLib.h"

using namespace CORE;

class BoilerOnlyAuton : public COREAuton{
public:
	BoilerOnlyAuton();
	void addNodes() override;

private:
	static Path * getPathFor(StartingPosition startingPosition);
	Node * m_driveToBoiler = nullptr;
	Node * m_dumpBallsInBoiler = nullptr;
	Node * m_resetHopper = nullptr;
	Node * m_shimmyHopper = nullptr;
	COREConstant<double> m_shimmyScale;
};



