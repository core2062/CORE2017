#pragma once
#include "CORERobotLib.h"

using namespace CORE;
class DriveDistanceAction : public COREAutonAction {
public:
    DriveDistanceAction(double speedInFraction, double distanceInFeet, bool setHighGear);
    void actionInit() override;
    COREAutonAction::actionStatus action() override;
    void actionEnd() override;

private:
	double m_speedInFraction;
    double m_distanceInInches;
    bool m_setHighGear;
    Timer m_initTime;
};
