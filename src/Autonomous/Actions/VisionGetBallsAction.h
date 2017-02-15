#pragma once

#include <memory>

#include "CORERobotLib.h"

class VisionGetBallsAction : public COREAutonAction {
public:
	VisionGetBallsAction();
    void actionInit() override;
    void actionEnd() override;
    actionStatus action() override;
private:

};
