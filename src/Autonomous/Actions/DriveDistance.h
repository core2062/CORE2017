#pragma once
#include "Robot.h"
#include "CORERobotLib.h"

class DriveDistance : public COREAutonAction {
public:
    DriveDistance();
    void actionInit() override;
    actionStatus action() override;
    void actionEnd() override;
private:
    double m_distanceInFeet;
	double m_speedInFraction;
};
