#pragma once

class AutonPaths{
public:
	static Path * getWallToPegPath(double speedScale = 1.0){
		switch(Robot->getStartingPosition()){
			case StartingPosition::BOILER:
				return PathLoader::loadPath("wallToPeg_boiler.csv", 1.0,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			case StartingPosition::FEEDER:
				return PathLoader::loadPath("wallToPeg_feeder.csv", 1.0,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			case StartingPosition::CENTER:
				return PathLoader::loadPath("wallToPeg_center.csv", 1.0,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			default:
				return nullptr;
				break;
		}
	}

	static Path * getWallToBoiler(double speedScale = 1.0){
		switch(Robot->getStartingPosition()){
			case StartingPosition::BOILER:
				return PathLoader::loadPath("gearToHopperAuton_forward_boiler.csv", 1.0,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			case StartingPosition::FEEDER:
				return PathLoader::loadPath("gearToHopperAuton_forward_feeder.csv", 1.0,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			case StartingPosition::CENTER:
				return PathLoader::loadPath("gearToHopperAuton_forward_center.csv", 1.0,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			default:
				return nullptr;
				break;
		}
	}

	static Path * getPegToHopperPath(double speedScale = 1.0){
		switch(Robot->getStartingPosition()){ //TODO: Check these file names, I'm pretty sure they're incorrect as they are same as above
			case StartingPosition::BOILER:
				return PathLoader::loadPath("gearToHopperAuton_forward_boiler.csv", 1.0,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			case StartingPosition::FEEDER:
				return PathLoader::loadPath("gearToHopperAuton_forward_feeder.csv", 1.0,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			case StartingPosition::CENTER:
				return PathLoader::loadPath("gearToHopperAuton_forward_center.csv", 1.0,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			default:
				return nullptr;
				break;
		}
	}
	static Path * getPegToBoilerPath(double speedScale = 1.0){
		switch(Robot->getStartingPosition()){
			case StartingPosition::BOILER:
				return PathLoader::loadPath("pegToBoiler_boiler.csv", 1.0,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			case StartingPosition::FEEDER:
				return PathLoader::loadPath("pegToBoiler_feeder.csv", 1.0,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			case StartingPosition::CENTER:
				return PathLoader::loadPath("pegToBoiler_center.csv", 1.0,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			default:
				return nullptr;
				break;
		}
	}
	static Path * getBoilerToHopperPath(double speedScale = 1.0){
		return PathLoader::loadPath("boilerToHopper.csv", 1.0, (CORERobot::getAlliance() == CORERobot::RED));
	}
	static Path * getHopperToBoilerPath(double speedScale = 1.0){
		return PathLoader::loadPath("hopperToBoiler_forward_center.csv", 1.0,
				(CORERobot::getAlliance() == CORERobot::RED));
	}
	static Path * getDriveForwardPath(double speedScale = 1.0) {
		return PathLoader::loadPath("driveForward.csv", 1.0, (CORERobot::getAlliance() == CORERobot::RED));
	}
	static Path * getPegReversePath(double speedScale = 1.0){
		switch(Robot->getStartingPosition()){
			case StartingPosition::BOILER:
				return PathLoader::loadPath("pegReverse_boiler.csv", 1.0,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			case StartingPosition::FEEDER:
				return PathLoader::loadPath("pegReverse_feeder.csv", 1.0,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			case StartingPosition::CENTER:
				return PathLoader::loadPath("pegReverse_center.csv", 1.0,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			default:
				return nullptr;
				break;
		}
	}
	static Path * getBoilerToWallPath(double speedScale = 1.0){
		switch(Robot->getStartingPosition()){
			case StartingPosition::BOILER:
				return PathLoader::loadPath("boilerAuton_reverse_boiler.csv", 1.0,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			case StartingPosition::FEEDER:
				return PathLoader::loadPath("boilerAuton_reverse_feeder.csv", 1.0,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			case StartingPosition::CENTER:
				return PathLoader::loadPath("boilerAuton_reverse_center.csv", 1.0,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			default:
				return nullptr;
				break;
		}
	}
	static Path * getHopperToWallPath(double speedScale = 1.0){
		switch(Robot->getStartingPosition()){
			case StartingPosition::BOILER:
				return PathLoader::loadPath("hopperAuton_reverse_boiler.csv", 1.0,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			case StartingPosition::FEEDER:
				return PathLoader::loadPath("hopperAuton_reverse_feeder.csv", 1.0,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			case StartingPosition::CENTER:
				return PathLoader::loadPath("hopperAuton_reverse_center.csv", 1.0,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			default:
				return nullptr;
				break;
		}
	}
};

