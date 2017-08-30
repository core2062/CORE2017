#include "AutonPaths.h"
#include "Robot.h"


using namespace CORE;

Path * AutonPaths::getWallToPegPath(double speedScale){
		switch(Robot->getStartingPosition()){
			case StartingPosition::BOILER:
				return PathLoader::loadPath("wallToPeg_boiler.csv", speedScale,
						(COREDriverstation::getAlliance() == COREDriverstation::RED));
				break;
			case StartingPosition::FEEDER:
				return PathLoader::loadPath("wallToPeg_feeder.csv", speedScale,
						(COREDriverstation::getAlliance() == COREDriverstation::RED));
				break;
			case StartingPosition::CENTER:
				return PathLoader::loadPath("wallToPeg_center.csv", speedScale,
						(COREDriverstation::getAlliance() == COREDriverstation::RED));
				break;
			default:
				return nullptr;
				break;
		}
	}

Path * AutonPaths::getApproachPegPath(double speedScale){
		switch(Robot->getStartingPosition()){
			case StartingPosition::BOILER:
				return PathLoader::loadPath("approachPeg_boiler.csv", speedScale,
						(COREDriverstation::getAlliance() == COREDriverstation::RED));
				break;
			case StartingPosition::FEEDER:
				return PathLoader::loadPath("approachPeg_feeder.csv", speedScale,
						(COREDriverstation::getAlliance() == COREDriverstation::RED));
				break;
			case StartingPosition::CENTER:
				return PathLoader::loadPath("approachPeg_center.csv", speedScale,
						(COREDriverstation::getAlliance() == COREDriverstation::RED));
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
						(COREDriverstation::getAlliance() == COREDriverstation::RED));
				break;
			case StartingPosition::FEEDER:
				return PathLoader::loadPath("gearToHopperAuton_forward_feeder.csv", speedScale,
						(COREDriverstation::getAlliance() == COREDriverstation::RED));
				break;
			case StartingPosition::CENTER:
				return PathLoader::loadPath("gearToHopperAuton_forward_center.csv", speedScale,
						(COREDriverstation::getAlliance() == COREDriverstation::RED));
				break;
			default:
				return nullptr;
				break;
			}

}
Path * AutonPaths::getPegToHopperPathA(double speedScale){

	return PathLoader::loadPath("pegToHopperA.csv", speedScale, (COREDriverstation::getAlliance() == COREDriverstation::RED));

	}

Path * AutonPaths::getPegToHopperPathB(double speedScale){

	return PathLoader::loadPath("pegToHopperB.csv", speedScale, (COREDriverstation::getAlliance() == COREDriverstation::RED));

	}

Path * AutonPaths::getPegToBoilerPath(double speedScale){
		switch(Robot->getStartingPosition()){
			case StartingPosition::BOILER:
				return PathLoader::loadPath("pegToBoiler_boiler.csv", speedScale,
						(COREDriverstation::getAlliance() == COREDriverstation::RED));
				break;
			case StartingPosition::FEEDER:
				return PathLoader::loadPath("pegToBoiler_feeder.csv", speedScale,
						(COREDriverstation::getAlliance() == COREDriverstation::RED));
				break;
			case StartingPosition::CENTER:
				return PathLoader::loadPath("pegToBoiler_center.csv", speedScale,
						(COREDriverstation::getAlliance() == COREDriverstation::RED));
				break;
			default:
				return nullptr;
				break;
		}
	}

Path * AutonPaths::getBoilerToHopperPath(double speedScale){
		return PathLoader::loadPath("boilerToHopper.csv", speedScale,
				(COREDriverstation::getAlliance() == COREDriverstation::RED));
	}

Path * AutonPaths::getHopperToBoilerPath(double speedScale){
		return PathLoader::loadPath("hopperToBoiler.csv", speedScale,
				(COREDriverstation::getAlliance() == COREDriverstation::RED));
	}

Path * AutonPaths::getDriveForwardPath(double speedScale) {
		return PathLoader::loadPath("driveForward.csv", speedScale,
				(COREDriverstation::getAlliance() == COREDriverstation::RED));
	}

Path * AutonPaths::getPegReversePath(double speedScale){
		switch(Robot->getStartingPosition()){
			case StartingPosition::BOILER:
				return PathLoader::loadPath("pegReverse_boiler.csv", speedScale,
						(COREDriverstation::getAlliance() == COREDriverstation::RED));
				break;
			case StartingPosition::FEEDER:
				return PathLoader::loadPath("pegReverse_feeder.csv", speedScale,
						(COREDriverstation::getAlliance() == COREDriverstation::RED));
				break;
			case StartingPosition::CENTER:
				return PathLoader::loadPath("pegReverse_center.csv", speedScale,
						(COREDriverstation::getAlliance() == COREDriverstation::RED));
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
						(COREDriverstation::getAlliance() == COREDriverstation::RED));
				break;
			case StartingPosition::FEEDER:
				return PathLoader::loadPath("boilerAuton_reverse_feeder.csv", speedScale,
						(COREDriverstation::getAlliance() == COREDriverstation::RED));
				break;
			case StartingPosition::CENTER:
				return PathLoader::loadPath("boilerAuton_reverse_center.csv", speedScale,
						(COREDriverstation::getAlliance() == COREDriverstation::RED));
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
						(COREDriverstation::getAlliance() == COREDriverstation::RED));
				break;
			case StartingPosition::FEEDER:
				return PathLoader::loadPath("hopperAuton_reverse_feeder.csv", speedScale,
						(COREDriverstation::getAlliance() == COREDriverstation::RED));
				break;
			case StartingPosition::CENTER:
				return PathLoader::loadPath("hopperAuton_reverse_center.csv", speedScale,
						(COREDriverstation::getAlliance() == COREDriverstation::RED));
				break;
			default:
				return nullptr;
				break;
		}
	}
Path * AutonPaths::getCrossFieldPath(double speedScale){
	if(Robot->getStartingPosition() != StartingPosition::FEEDER){
		return PathLoader::loadPath("boilerToOpposite.csv", speedScale,
				(COREDriverstation::getAlliance() == COREDriverstation::RED));
	} else {
		return PathLoader::loadPath("boilerToCross_feeder.csv", speedScale,
				(COREDriverstation::getAlliance() == COREDriverstation::RED));
	}
	}

Path * AutonPaths::getPegToCrossPathA(double speedScale){
		switch(Robot->getStartingPosition()){
			case StartingPosition::BOILER:
				return PathLoader::loadPath("pegToCrossA_boiler.csv", 1.0,
						(COREDriverstation::getAlliance() == COREDriverstation::RED));
				break;
			case StartingPosition::FEEDER:
				return PathLoader::loadPath("pegToCrossA_feeder.csv", 1.0,
						(COREDriverstation::getAlliance() == COREDriverstation::RED));
				break;
			case StartingPosition::CENTER:
				return PathLoader::loadPath("pegToCrossA_center.csv", 1.0,
						(COREDriverstation::getAlliance() == COREDriverstation::RED));
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
				(COREDriverstation::getAlliance() == COREDriverstation::RED));
			break;
		case StartingPosition::FEEDER:
			return PathLoader::loadPath("pegToCrossB_feeder.csv", 1.0,
				(COREDriverstation::getAlliance() == COREDriverstation::RED));
			break;
		case StartingPosition::CENTER:
			return PathLoader::loadPath("pegToCrossB_center.csv", 1.0,
				(COREDriverstation::getAlliance() == COREDriverstation::RED));
			break;
	default:
			return nullptr;
			break;
			}
}
Path * AutonPaths::getWallToHopperPath(double speedscale){
			return PathLoader::loadPath("wallToHopper.csv", 1.0,
					(COREDriverstation::getAlliance() == COREDriverstation::RED));

}

Path * AutonPaths::getReverseHopperPath(double speedScale){

	return PathLoader::loadPath("backupFromHopper.csv", 1.0,
		(COREDriverstation::getAlliance() == COREDriverstation::RED));

}
Path * AutonPaths::getReverseBoilerPath(double speedScale){

	return PathLoader::loadPath("backupFromBoiler.csv.csv", 1.0,
		(COREDriverstation::getAlliance() == COREDriverstation::RED));


}

Path * AutonPaths::getBoilerToPegPath(double speedScale){
	return getPegToBoilerPath(speedScale);
}

Path * AutonPaths::getWallToFarHopperPath(double speedScale){
	//TODO Add the csv file for this path
	switch(Robot->getStartingPosition()){
		case StartingPosition::BOILER:
			return PathLoader::loadPath("wallToHopper_boiler.csv", 1.0,
					(COREDriverstation::getAlliance() == COREDriverstation::RED));
			break;
		case StartingPosition::FEEDER:
			return PathLoader::loadPath("wallToHopper_feeder.csv", 1.0,
					(COREDriverstation::getAlliance() == COREDriverstation::RED));
			break;
		case StartingPosition::CENTER:
			return PathLoader::loadPath("wallToHopper_center.csv", 1.0,
					(COREDriverstation::getAlliance() == COREDriverstation::RED));
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
					(COREDriverstation::getAlliance() == COREDriverstation::RED));
			break;
		case StartingPosition::FEEDER:
			return PathLoader::loadPath("wallToHopper_feeder.csv", 1.0,
					(COREDriverstation::getAlliance() == COREDriverstation::RED));
			break;
		case StartingPosition::CENTER:
			return PathLoader::loadPath("wallToHopper_center.csv", 1.0,
					(COREDriverstation::getAlliance() == COREDriverstation::RED));
			break;
		default:
			return nullptr;
			break;
	}

}

