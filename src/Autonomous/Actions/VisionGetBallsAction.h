#pragma once

#include <memory>

#include "CORERobotLib.h"

using namespace CORE;

class VisionGetBallsAction : public COREAutonAction {
public:
	VisionGetBallsAction();
    void actionInit() override;
    void actionEnd() override;
    actionStatus action() override;
private:

};
