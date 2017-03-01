#pragma once;

#include <memory>
#include "CORERobotLib.h"

using namespace CORE;

class DoNothingAuton : public COREAuton{
public:
	DoNothingAuton();
	void addNodes() override;
};


