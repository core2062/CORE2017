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
	Node * m_driveToBoiler;
	Node * m_dumpBallsInBoiler;
	Node * m_resetHopper;
	Node * m_shimmyHopper;
	COREConstant<double> m_shimmyScale;
};



