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

	Node * m_driveA = nullptr;
	Node * m_driveB = nullptr;
	Node * m_driveC = nullptr;
	Node * m_driveD = nullptr;
	Node * m_driveE = nullptr;
	Node * m_driveF = nullptr;


};

