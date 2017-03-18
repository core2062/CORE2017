#include "AutonPaths.h"
#include "Robot.h"

using namespace CORE;

Path * AutonPaths::getWallToPegPath(double speedScale){
		switch(Robot->getStartingPosition()){
			case StartingPosition::BOILER:
				return PathLoader::loadPath("gearAuton_forward_boiler.csv", speedScale,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			case StartingPosition::FEEDER:
				return PathLoader::loadPath("gearAuton_forward_feeder.csv", speedScale,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			case StartingPosition::CENTER:
				return PathLoader::loadPath("gearAuton_forward_center.csv", speedScale,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			default:
				return nullptr;
				break;
		}
	}
Path * AutonPaths::getWallToBoilerPath(double speedScale){
		switch(Robot->getStartingPosition()){ //TODO: Check these file names, I'm pretty sure they're incorrect as they are same as above
			case StartingPosition::BOILER:
				return PathLoader::loadPath("gearToHopperAuton_forward_boiler.csv", speedScale,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			case StartingPosition::FEEDER:
				return PathLoader::loadPath("gearToHopperAuton_forward_feeder.csv", speedScale,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			case StartingPosition::CENTER:
				return PathLoader::loadPath("gearToHopperAuton_forward_center.csv", speedScale,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			default:
				return nullptr;
				break;
			}

}
Path * AutonPaths::getPegToHopperPath(double speedScale){
		switch(Robot->getStartingPosition()){ //TODO: Check these file names, I'm pretty sure they're incorrect as they are same as above
			case StartingPosition::BOILER:
				return PathLoader::loadPath("gearToHopperAuton_forward_boiler.csv", speedScale,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			case StartingPosition::FEEDER:
				return PathLoader::loadPath("gearToHopperAuton_forward_feeder.csv", speedScale,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			case StartingPosition::CENTER:
				return PathLoader::loadPath("gearToHopperAuton_forward_center.csv", speedScale,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			default:
				return nullptr;
				break;
		}
	}

Path * AutonPaths::getPegToBoilerPath(double speedScale){
		switch(Robot->getStartingPosition()){
			case StartingPosition::BOILER:
				return PathLoader::loadPath("gearToBoilerAuton_forward_boiler.csv", speedScale,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			case StartingPosition::FEEDER:
				return PathLoader::loadPath("gearToBoilerAuton_forward_feeder.csv", speedScale,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			case StartingPosition::CENTER:
				return PathLoader::loadPath("gearToBoilerAuton_forward_center.csv", speedScale,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			default:
				return nullptr;
				break;
		}
	}

Path * AutonPaths::getBoilerToHopperPath(double speedScale){
		return PathLoader::loadPath("boilerToHopper.csv", speedScale,
				(CORERobot::getAlliance() == CORERobot::RED));
	}

Path * AutonPaths::getHopperToBoilerPath(double speedScale){
		return PathLoader::loadPath("hopperToBoiler_forward_center.csv", speedScale,
				(CORERobot::getAlliance() == CORERobot::RED));
	}

Path * AutonPaths::getDriveForwardPath(double speedScale) {
		return PathLoader::loadPath("driveForward.csv", speedScale,
				(CORERobot::getAlliance() == CORERobot::RED));
	}

Path * AutonPaths::getPegReversePath(double speedScale){
		switch(Robot->getStartingPosition()){
			case StartingPosition::BOILER:
				return PathLoader::loadPath("gearAuton_reverse_boiler.csv", speedScale,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			case StartingPosition::FEEDER:
				return PathLoader::loadPath("gearAuton_reverse_feeder.csv", speedScale,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			case StartingPosition::CENTER:
				return PathLoader::loadPath("gearAuton_reverse_center.csv", speedScale,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			default:
				return nullptr;
				break;
		}
	}

Path * AutonPaths::backupFromBoilerPath(double speedScale){
		switch(Robot->getStartingPosition()){
			case StartingPosition::BOILER:
				return PathLoader::loadPath("boilerAuton_reverse_boiler.csv", speedScale,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			case StartingPosition::FEEDER:
				return PathLoader::loadPath("boilerAuton_reverse_feeder.csv", speedScale,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			case StartingPosition::CENTER:
				return PathLoader::loadPath("boilerAuton_reverse_center.csv", speedScale,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			default:
				return nullptr;
				break;
		}
	}

Path * AutonPaths::backupFromHopperPath(double speedScale){
		switch(Robot->getStartingPosition()){
			case StartingPosition::BOILER:
				return PathLoader::loadPath("hopperAuton_reverse_boiler.csv", speedScale,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			case StartingPosition::FEEDER:
				return PathLoader::loadPath("hopperAuton_reverse_feeder.csv", speedScale,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			case StartingPosition::CENTER:
				return PathLoader::loadPath("hopperAuton_reverse_center.csv", speedScale,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			default:
				return nullptr;
				break;
		}
	}

