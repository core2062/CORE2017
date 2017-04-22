#pragma once

#include "CORERobotLib.h"
#include "TurnAngleAction.h"
#include "DriveDistanceAction.h"
#include "WPILib.h"

using namespace CORE;

class PickupGearWithVisionAction : public COREAutonAction {
public:
	PickupGearWithVisionAction(double pixelViewRange = 100, double ultraDistance = 13,
			double secondsAfterPickupIsDown = .5);
	void actionInit() override;
	COREAutonAction::actionStatus action() override;
	void actionEnd() override;
private:
	double m_pixelViewRange;
	double m_ultraDistance;
	double m_secondsAfterPickupIsDown;
	CORETimer m_cameraStabilizationInterval;
	TurnAngleAction* m_turnAction = nullptr;
	DriveDistanceAction * m_driveDistance = nullptr;
	bool m_shouldTurn = false;
	double distanceToGear = 0.0;

};
