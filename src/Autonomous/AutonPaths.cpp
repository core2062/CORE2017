#include "AutonPaths.h"
#include "Robot.h"


using namespace CORE;

Path * AutonPaths::getWallToPegPath(double speedScale){
		switch(Robot->getStartingPosition()){
			case StartingPosition::BOILER:
				return PathLoader::loadPath("wallToPeg_forward_boiler.csv", speedScale,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			case StartingPosition::FEEDER:
				return PathLoader::loadPath("wallToPeg_forward_feeder.csv", speedScale,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			case StartingPosition::CENTER:
				return PathLoader::loadPath("wallToPeg_forward_center.csv", speedScale,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			default:
				return nullptr;
				break;
		}
	}
Path * AutonPaths::getWallToBoilerPath(double speedScale){
		switch(Robot->getStartingPosition()){
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
		switch(Robot->getStartingPosition()){
			case StartingPosition::BOILER:
				return PathLoader::loadPath("pegToHopper_forward_boiler.csv", speedScale,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			case StartingPosition::FEEDER:
				return PathLoader::loadPath("pegToHopper_forward_feeder.csv", speedScale,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			case StartingPosition::CENTER:
				return PathLoader::loadPath("pegToHopper_forward_center.csv", speedScale,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			default:
				return nullptr;
				break;
		}
	}

Path * AutonPaths::getPegToBoilerPath(double speedScale, bool reverse){
		switch(Robot->getStartingPosition()){
			case StartingPosition::BOILER:
				return PathLoader::loadPath("pegToBoiler_forward_boiler.csv", speedScale,
						(CORERobot::getAlliance() == CORERobot::RED), reverse);
				break;
			case StartingPosition::FEEDER:
				return PathLoader::loadPath("pegToBoiler_forward_feeder.csv", speedScale,
						(CORERobot::getAlliance() == CORERobot::RED), reverse);
				break;
			case StartingPosition::CENTER:
				return PathLoader::loadPath("pegToBoiler_forward_center.csv", speedScale,
						(CORERobot::getAlliance() == CORERobot::RED), reverse);
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
		return PathLoader::loadPath("hopperToBoiler.csv", speedScale,
				(CORERobot::getAlliance() == CORERobot::RED));
	}

Path * AutonPaths::getDriveForwardPath(double speedScale) {
		return PathLoader::loadPath("driveForward.csv", speedScale,
				(CORERobot::getAlliance() == CORERobot::RED));
	}

Path * AutonPaths::getPegReversePath(double speedScale){
		switch(Robot->getStartingPosition()){
			case StartingPosition::BOILER:
				return PathLoader::loadPath("pegReverse_reverse_boiler.csv", speedScale,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			case StartingPosition::FEEDER:
				return PathLoader::loadPath("pegReverse_reverse_feeder.csv", speedScale,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			case StartingPosition::CENTER:
				return PathLoader::loadPath("pegReverse_reverse_center.csv", speedScale,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			default:
				return nullptr;
				break;
		}
	}

Path * AutonPaths::getBoilerToWallPath(double speedScale){
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

Path * AutonPaths::getHopperToWallPath(double speedScale){
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
Path * AutonPaths::getCrossFieldPath(double speedScale){
		return PathLoader::loadPath("boilerToOpposite.csv", speedScale,
				(CORERobot::getAlliance() == CORERobot::RED));
	}

Path * AutonPaths::getPegToCrossPathA(double speedScale){
		switch(Robot->getStartingPosition()){
			case StartingPosition::BOILER:
				return PathLoader::loadPath("pegToCrossA_boiler.csv", 1.0,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			case StartingPosition::FEEDER:
				return PathLoader::loadPath("pegToCrossA_feeder.csv", 1.0,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			case StartingPosition::CENTER:
				return PathLoader::loadPath("pegToCrossA_center.csv", 1.0,
						(CORERobot::getAlliance() == CORERobot::RED));
				break;
			default:
				return nullptr;
				break;
		}
}
Path * AutonPaths::getPegToCrossPathB(double speedScale){
	switch(Robot->getStartingPosition()){
		case StartingPosition::BOILER:
			return PathLoader::loadPath("pegToCrossB_boiler.csv", 1.0,
				(CORERobot::getAlliance() == CORERobot::RED));
			break;
		case StartingPosition::FEEDER:
			return PathLoader::loadPath("pegToCrossB_feeder.csv", 1.0,
				(CORERobot::getAlliance() == CORERobot::RED));
			break;
		case StartingPosition::CENTER:
			return PathLoader::loadPath("pegToCrossB_center.csv", 1.0,
				(CORERobot::getAlliance() == CORERobot::RED));
			break;
	default:
			return nullptr;
			break;
			}
}
Path * AutonPaths::getWallToHopperPath(double speedscale){

	switch(Robot->getStartingPosition()){
		case StartingPosition::BOILER:
			return PathLoader::loadPath("wallToHopper_boiler.csv", 1.0,
					(CORERobot::getAlliance() == CORERobot::RED));
			break;
		case StartingPosition::FEEDER:
			return PathLoader::loadPath("wallToHopper_feeder.csv", 1.0,
					(CORERobot::getAlliance() == CORERobot::RED));
			break;
		case StartingPosition::CENTER:
			return PathLoader::loadPath("wallToHopper_center.csv", 1.0,
					(CORERobot::getAlliance() == CORERobot::RED));
			break;
		default:
			return nullptr;
			break;
	}

}

Path * AutonPaths::getReverseHopperPath(double speedScale){

	return PathLoader::loadPath("backupFromHopper.csv", 1.0,
		(CORERobot::getAlliance() == CORERobot::RED));

}
Path * AutonPaths::getReverseBoilerPath(double speedScale){

	return PathLoader::loadPath("backupFromBoiler.csv.csv", 1.0,
		(CORERobot::getAlliance() == CORERobot::RED));


}

Path * AutonPaths::getBoilerToPegPath(double speedScale){
	return getPegToBoilerPath(speedScale, true);
}

Path * AutonPaths::getWallToFarHopperPath(double speedScale){
	//TODO Add the csv file for this path
	switch(Robot->getStartingPosition()){
		case StartingPosition::BOILER:
			return PathLoader::loadPath("wallToHopper_boiler.csv", 1.0,
					(CORERobot::getAlliance() == CORERobot::RED));
			break;
		case StartingPosition::FEEDER:
			return PathLoader::loadPath("wallToHopper_feeder.csv", 1.0,
					(CORERobot::getAlliance() == CORERobot::RED));
			break;
		case StartingPosition::CENTER:
			return PathLoader::loadPath("wallToHopper_center.csv", 1.0,
					(CORERobot::getAlliance() == CORERobot::RED));
			break;
		default:
			return nullptr;
			break;
	}

}

Path * AutonPaths::getFarHopperToBoilerPath(double speedScale){
	//TODO Add the file that goes from the far hopper to the boiler
	switch(Robot->getStartingPosition()){
		case StartingPosition::BOILER:
			return PathLoader::loadPath("wallToHopper_boiler.csv", 1.0,
					(CORERobot::getAlliance() == CORERobot::RED));
			break;
		case StartingPosition::FEEDER:
			return PathLoader::loadPath("wallToHopper_feeder.csv", 1.0,
					(CORERobot::getAlliance() == CORERobot::RED));
			break;
		case StartingPosition::CENTER:
			return PathLoader::loadPath("wallToHopper_center.csv", 1.0,
					(CORERobot::getAlliance() == CORERobot::RED));
			break;
		default:
			return nullptr;
			break;
	}

}

