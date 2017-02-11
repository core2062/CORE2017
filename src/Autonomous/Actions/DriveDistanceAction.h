#pragma once
#include "Robot.h"
#include "CORERobotLib.h"

class DriveDistanceAction : public COREAutonAction {
public:
    DriveDistanceAction();
    void actionInit() override;
    actionStatus action() override;
    void actionEnd() override;
private:
    double m_distanceInFeet;
	double m_speedInFraction;
};
