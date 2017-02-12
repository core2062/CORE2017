#pragma once
#include "Robot.h"
#include "CORERobotLib.h"

class DriveDistance : public COREAutonAction {
public:
    DriveDistance(double speedInFraction, double distanceInFeet);
    void actionInit() override;
    actionStatus action() override;
    void actionEnd() override;
private:
	double m_speedInFraction;
    double m_distanceInFeet;
};
