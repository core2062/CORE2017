#include "Actions.h"
#include "Robot.h"
#include <Autonomous/GearHopperBoilerAuton.h>
#include "AutonPaths.h"

GearHopperBoilerAuton::GearHopperBoilerAuton() :
	COREAuton("Gear, Boiler and Hopper Auton", 0.0),
	m_shimmyScale("Shimmy Scale", 0.0){

	}

void GearHopperBoilerAuton::addNodes(){
	m_driveToPeg = new Node(15, new DriveWaypointAction(PathLoader::loadPath("drivetopeg.csv", 1.0, true, true)));
	m_loadGearOnPeg = new Node(1, new LoadGearOntoPegAction());
	m_backupFromPeg = new Node(15, new DriveWaypointAction(PathLoader::loadPath("backupfrompeg.csv", 1.0, true, true)));
	m_driveToHopper = new Node(15, new DriveWaypointAction(PathLoader::loadPath("drivetohopper.csv", 1.0, true, true)));
	m_loadHopper = new Node(3, new HopperFlapAction());
	m_backupFromHopper = new Node(15, new DriveWaypointAction(PathLoader::loadPath("backupfromhopper.csv", 1.0, true, true)));
	m_driveToBoiler = new Node(15, new DriveWaypointAction(PathLoader::loadPath("drivetoboiler.csv", 1.0, true, true)));
	m_dumpBallsInBoiler = new Node(4, new DumpBallsAction(true));
	m_shimmyHopper = new Node(3, new ShimmyAction(0.0, 0.0));
	m_resetHopper = new Node(3, new DumpBallsAction(true));

	addFirstNode(m_driveToPeg);
	m_driveToPeg->addNext(m_loadGearOnPeg),
	m_loadGearOnPeg->addNext(m_backupFromPeg),
	m_backupFromPeg->addNext(m_driveToHopper),
	m_driveToHopper->addNext(m_loadHopper),
	m_loadHopper->addNext(m_backupFromHopper),
	m_backupFromHopper->addNext(m_driveToBoiler),
	m_driveToBoiler->addNext(m_dumpBallsInBoiler),
	m_dumpBallsInBoiler->addNext(m_shimmyHopper),
	m_shimmyHopper->addNext(m_resetHopper);
	}

Path* GearHopperBoilerAuton::getPathForPeg(StartingPosition startingPosition){
	switch(startingPosition){
		case StartingPosition::BOILER:
			return PathLoader::loadPath("gearHopperBoilerAuton_getPathForPeg_boiler.csv", 1.0, (CORERobot::getAlliance() == RED));
			break;
		case StartingPosition::FEEDER:
			return PathLoader::loadPath("gearHopperBoilerAuton_getPathForPeg_feeder.csv", 1.0, (CORERobot::getAlliance() == RED));
			break;
		default:
			//return AutonPaths::getForwardPegPath();
			return PathLoader::loadPath("gearAuton_forward_center.csv", 1.0, (CORERobot::getAlliance() == RED));
			break;
	}
}

Path * GearHopperBoilerAuton::backupFromPeg(StartingPosition startingPosition){
	switch(startingPosition){
		case StartingPosition::BOILER:
			return PathLoader::loadPath("gearHopperBoilerAuton_backupFromPeg_boiler.csv", 1.0, (CORERobot::getAlliance() == RED));
			break;
		case StartingPosition::FEEDER:
			return PathLoader::loadPath("gearHopperBoilerAuton_backupFromPeg_feeder.csv", 1.0, (CORERobot::getAlliance() == RED));
			break;
		default:
			//return AutonPaths::getReversePegPath();
			return PathLoader::loadPath("gearAuton_forward_center.csv", 1.0, (CORERobot::getAlliance() == RED));
			break;
	}
}

Path * GearHopperBoilerAuton::driveToHopper(StartingPosition startingPosition){
	switch(startingPosition){
		case StartingPosition::BOILER:
			return PathLoader::loadPath("gearHopperBoilerAuton_driveToHopper_boiler.csv", 1.0, (CORERobot::getAlliance() == RED));
			break;
		case StartingPosition::FEEDER:
			return PathLoader::loadPath("gearHopperBoilerAuton_driveToHopper_feeder.csv", 1.0, (CORERobot::getAlliance() == RED));
			break;
		default:
			//return AutonPaths::getForwardHopperPath();
			return PathLoader::loadPath("gearAuton_forward_center.csv", 1.0, (CORERobot::getAlliance() == RED));
			break;
	}
}

Path* GearHopperBoilerAuton::backupFromHopper(StartingPosition startingPosition) {
	switch(startingPosition){
		case StartingPosition::BOILER:
			return PathLoader::loadPath("gearHopperBoilerAuton_backupFromHopper_boiler.csv", 1.0, (CORERobot::getAlliance() == RED));
			break;
		case StartingPosition::FEEDER:
			return PathLoader::loadPath("gearHopperBoilerAuton_backupFromHopper_feeder.csv", 1.0, (CORERobot::getAlliance() == RED));
			break;
		default:
			//return AutonPaths::getReverseHopperPath();
			return PathLoader::loadPath("gearAuton_forward_center.csv", 1.0, (CORERobot::getAlliance() == RED));
			break;
	}
}

Path* GearHopperBoilerAuton::driveToBoiler(StartingPosition startingPosition) {
	switch(startingPosition){
		case StartingPosition::BOILER:
			return PathLoader::loadPath("gearHopperBoilerAuton_driveToBoiler_boiler.csv", 1.0, (CORERobot::getAlliance() == RED));
			break;
		case StartingPosition::FEEDER:
			return PathLoader::loadPath("gearHopperBoilerAuton_driveToBoiler_feeder.csv", 1.0, (CORERobot::getAlliance() == RED));
			break;
		default:
			//return AutonPaths::getForwardBoilerPath();
			return PathLoader::loadPath("gearAuton_forward_center.csv", 1.0, (CORERobot::getAlliance() == RED));
			break;
	}
}
