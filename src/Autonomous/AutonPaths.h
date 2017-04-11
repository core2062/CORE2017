#pragma once

#include "Robot.h"

class AutonPaths{
public:
	static Path * getWallToPegPath(double speedScale = 1.0);

	static Path * getWallToBoilerPath(double speedScale = 1.0);

	static Path * getPegToHopperPathA(double speedScale = 1.0);

	static Path * getPegToHopperPathB(double speedScale = 1.0);

	static Path * getPegToBoilerPath(double speedScale = 1.0, bool reverse = false);

	static Path * getBoilerToHopperPath(double speedScale = 1.0);

	static Path * getHopperToBoilerPath(double speedScale = 1.0);

	static Path * getDriveForwardPath(double speedScale = 1.0);

	static Path * getPegReversePath(double speedScale = 1.0);

	static Path * getBoilerToWallPath(double speedScale = 1.0);

	static Path * getHopperToWallPath(double speedScale = 1.0);

	static Path * getCrossFieldPath(double speedScale = 1.0);

	static Path * getPegToCrossPathA(double speedScale = 1.0);

	static Path * getPegToCrossPathB(double speedScale = 1.0);

	static Path * getWallToHopperPath(double speedScale = 1.0);

	static Path * getReverseHopperPath(double speedScale = 1.0);

	static Path * getReverseBoilerPath(double speedScale = 1.0);

	static Path * getBoilerToPegPath(double speedScale = 1.0);

	static Path * getWallToFarHopperPath(double speedScale = 1.0);

	static Path * getFarHopperToBoilerPath(double speedScale = 1.0);

};

