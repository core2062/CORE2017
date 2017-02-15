#pragma once
#include "CORERobotLib.h"

class DriveDistanceAction : public COREAutonAction {
public:
    DriveDistanceAction(double speedInFraction, double distanceInFeet);
    void actionInit() override;
    actionStatus action() override;
    void actionEnd() override;
private:
	double m_speedInFraction;
    double m_distanceInFeet;
};
