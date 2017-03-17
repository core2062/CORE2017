#pragma once

#include "CORERobotLib.h"
#include "src/WaypointFollower/PathLoader.h"

class AutonPaths{
public:
	static Path * getWallToPegPath(double speedScale = 1.0);

	static Path * getWallToBoilerPath(double speedScale = 1.0);

	static Path * getPegToHopperPath(double speedScale = 1.0);

	static Path * getPegToBoilerPath(double speedScale = 1.0);

	static Path * getBoilerToHopperPath(double speedScale = 1.0);

	static Path * getHopperToBoilerPath(double speedScale = 1.0);

	static Path * getDriveForwardPath(double speedScale = 1.0);

	static Path * getPegReversePath(double speedScale = 1.0);

	static Path * backupFromBoilerPath(double speedScale = 1.0);

	static Path * backupFromHopperPath(double speedScale = 1.0);

};

