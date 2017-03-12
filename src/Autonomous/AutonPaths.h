#pragma once

class AutonPaths{
public:
	static Path * getWallToPegPath(double speedScale = 1.0){
		switch(Robot->getStartingPosition()){
			case StartingPosition::BOILER:
				return PathLoader::loadPath("gearAuton_forward_boiler.csv", 1.0, (CORERobot::getAlliance() == RED));
				break;
			case StartingPosition::FEEDER:
				return PathLoader::loadPath("gearAuton_forward_feeder.csv", 1.0, (CORERobot::getAlliance() == RED));
				break;
			case StartingPosition::CENTER:
				return PathLoader::loadPath("gearAuton_forward_center.csv", 1.0, (CORERobot::getAlliance() == RED));
				break;
			default:
				return nullptr;
				break;
		}
	}

	static Path * getWallToBoiler(double speedScale = 1.0){
		switch(Robot->getStartingPosition()){
			case StartingPosition::BOILER:
				return PathLoader::loadPath("gearToHopperAuton_forward_boiler.csv", 1.0, (CORERobot::getAlliance() == RED));
				break;
			case StartingPosition::FEEDER:
				return PathLoader::loadPath("gearToHopperAuton_forward_feeder.csv", 1.0, (CORERobot::getAlliance() == RED));
				break;
			case StartingPosition::CENTER:
				return PathLoader::loadPath("gearToHopperAuton_forward_center.csv", 1.0, (CORERobot::getAlliance() == RED));
				break;
			default:
				return nullptr;
				break;
		}
	}

	static Path * getPegToHopperPath(double speedScale = 1.0){
		switch(Robot->getStartingPosition()){
			case StartingPosition::BOILER:
				return PathLoader::loadPath("gearToHopperAuton_forward_boiler.csv", 1.0, (CORERobot::getAlliance() == RED));
				break;
			case StartingPosition::FEEDER:
				return PathLoader::loadPath("gearToHopperAuton_forward_feeder.csv", 1.0, (CORERobot::getAlliance() == RED));
				break;
			case StartingPosition::CENTER:
				return PathLoader::loadPath("gearToHopperAuton_forward_center.csv", 1.0, (CORERobot::getAlliance() == RED));
				break;
			default:
				return nullptr;
				break;
		}
	}
	static Path * getPegToBoilerPath(double speedScale = 1.0){
		switch(Robot->getStartingPosition()){
			case StartingPosition::BOILER:
				return PathLoader::loadPath("gearToBoilerAuton_forward_boiler.csv", 1.0, (CORERobot::getAlliance() == RED));
				break;
			case StartingPosition::FEEDER:
				return PathLoader::loadPath("gearToBoilerAuton_forward_feeder.csv", 1.0, (CORERobot::getAlliance() == RED));
				break;
			case StartingPosition::CENTER:
				return PathLoader::loadPath("gearToBoilerAuton_forward_center.csv", 1.0, (CORERobot::getAlliance() == RED));
				break;
			default:
				return nullptr;
				break;
		}
	}
	static Path * getBoilerToHopperPath(double speedScale = 1.0){
		return PathLoader::loadPath("boilerToHopper.csv", 1.0, (CORERobot::getAlliance() == RED));
	}
	static Path * getHopperToBoilerPath(double speedScale = 1.0){
		return PathLoader::loadPath("hopperToBoiler_forward_center.csv", 1.0, (CORERobot::getAlliance() == RED));
	}
	static Path * getDriveForwardPath(double speedScale = 1.0){
		return PathLoader::loadPath("driveForward_forward_center.csv", 1.0, (CORERobot::getAlliance() == RED));
	}
	static Path * getPegToWallPath(double speedScale = 1.0){
		switch(Robot->getStartingPosition()){
			case StartingPosition::BOILER:
				return PathLoader::loadPath("gearAuton_backwards_boiler.csv", 1.0, (CORERobot::getAlliance() == RED));
				break;
			case StartingPosition::FEEDER:
				return PathLoader::loadPath("gearAuton_backwards_feeder.csv", 1.0, (CORERobot::getAlliance() == RED));
				break;
			case StartingPosition::CENTER:
				return PathLoader::loadPath("gearAuton_backwards_center.csv", 1.0, (CORERobot::getAlliance() == RED));
				break;
			default:
				return nullptr;
				break;
		}
	}
	static Path * getBoilerToWallPath(double speedScale = 1.0){
		switch(Robot->getStartingPosition()){
			case StartingPosition::BOILER:
				return PathLoader::loadPath("boilerAuton_backwards_boiler.csv", 1.0, (CORERobot::getAlliance() == RED));
				break;
			case StartingPosition::FEEDER:
				return PathLoader::loadPath("boilerAuton_backwards_feeder.csv", 1.0, (CORERobot::getAlliance() == RED));
				break;
			case StartingPosition::CENTER:
				return PathLoader::loadPath("boilerAuton_backwards_center.csv", 1.0, (CORERobot::getAlliance() == RED));
				break;
			default:
				return nullptr;
				break;
		}
	}
	static Path * getHopperToWallPath(double speedScale = 1.0){
		switch(Robot->getStartingPosition()){
			case StartingPosition::BOILER:
				return PathLoader::loadPath("hopperAuton_backwards_boiler.csv", 1.0, (CORERobot::getAlliance() == RED));
				break;
			case StartingPosition::FEEDER:
				return PathLoader::loadPath("hopperAuton_backwards_feeder.csv", 1.0, (CORERobot::getAlliance() == RED));
				break;
			case StartingPosition::CENTER:
				return PathLoader::loadPath("hopperAuton_backwards_center.csv", 1.0, (CORERobot::getAlliance() == RED));
				break;
			default:
				return nullptr;
				break;
		}
	}
};

