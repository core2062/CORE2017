#include "Actions.h"
#include "Robot.h"
#include <Autonomous/GearBoilerHopperAuton.h>
#include "AutonPaths.h"

GearBoilerHopperAuton::GearBoilerHopperAuton(StartingPosition startingPosition) :
	COREAuton("Gear and Hopper Auton", 0.0){


}

void GearBoilerHopperAuton::addNodes() {
	m_driveToPeg = new Node(15, new DriveWaypointAction(PathLoader::loadPath("drivetopeg.csv", 1.0, true, true)));
	m_loadGearOnPeg = new Node(15, new LoadGearOntoPegAction());
	m_backupFromPeg = new Node(15, new DriveWaypointAction(PathLoader::loadPath("backupfrompeg.csv", 1.0, true, true)));
	m_driveToBoiler = new Node(15, new DriveWaypointAction(PathLoader::loadPath("drivetoboiler.csv", 1.0, true, true)));
	m_dumpBallsInBoiler = new Node(15, new DumpBallsAction(false));
	m_shimmyHopper = new Node(15, new ShimmyAction(0.0, 0.0));
	m_backupFromBoiler = new Node(15, new DriveWaypointAction(PathLoader::loadPath("backupfromboiler.csv", 1.0, true, true)));
	m_driveToHopper = new Node(15, new DriveWaypointAction(PathLoader::loadPath("drivetohopper.csv", 1.0, true, true)));
	m_loadHopper = new Node(3, new HopperFlapAction());

	addFirstNode(m_driveToPeg);
	m_driveToPeg->addNext(m_loadGearOnPeg),
	m_loadGearOnPeg->addNext(m_backupFromPeg),
	m_backupFromPeg->addNext(m_driveToBoiler),
	m_driveToBoiler->addNext(m_dumpBallsInBoiler),
	m_dumpBallsInBoiler->addNext(m_shimmyHopper),
	m_shimmyHopper->addNext(m_backupFromBoiler),
	m_backupFromBoiler->addNext(m_driveToHopper),
	m_driveToHopper->addNext(m_loadHopper);

}

Path* GearBoilerHopperAuton::getPathForPeg(StartingPosition startingPosition) {
	switch(startingPosition){
		case StartingPosition::BOILER:
			return PathLoader::loadPath("gearBoilerAuton_driveToPeg_boiler.csv", 1.0, (CORERobot::getAlliance() == RED));
			break;
		case StartingPosition::FEEDER:
			return PathLoader::loadPath("gearBoilerAuton_driveToPeg_feeder.csv", 1.0, (CORERobot::getAlliance() == RED));
			break;
		default:
			return PathLoader::loadPath("gearAuton_forward_center.csv", 1.0, (CORERobot::getAlliance() == RED));
			//return AutonPaths::getForwardPegPath();
			break;
	}
}

Path* GearBoilerHopperAuton::backupFromPeg(StartingPosition startingPosition) {
	switch(startingPosition){
		case StartingPosition::BOILER:
			return PathLoader::loadPath("gearBoilerAuton_backupFromPeg_boiler.csv", 1.0, (CORERobot::getAlliance() == RED));
			break;
		case StartingPosition::FEEDER:
			return PathLoader::loadPath("gearBoilerAuton_backupFromPeg_feeder.csv", 1.0, (CORERobot::getAlliance() == RED));
			break;
		default:
			return PathLoader::loadPath("gearAuton_forward_center.csv", 1.0, (CORERobot::getAlliance() == RED));
			//return AutonPaths::getReversePegPath();
			break;
	}
}

Path * GearBoilerHopperAuton::driveToBoiler(StartingPosition startingPosition) {
	switch(startingPosition){
		case StartingPosition::BOILER:
			return PathLoader::loadPath("gearBoilerAuton_driveToBoiler_boiler.csv", 1.0, (CORERobot::getAlliance() == RED));
			break;
		case StartingPosition::FEEDER:
			return PathLoader::loadPath("gearBoilerAuton_driveToBoiler_feeder.csv", 1.0, (CORERobot::getAlliance() == RED));
			break;
		default:
			//return AutonPaths::getForwardBoilerPath();
			return PathLoader::loadPath("gearAuton_forward_center.csv", 1.0, (CORERobot::getAlliance() == RED));
			break;
	}
}

Path* GearBoilerHopperAuton::backupFromBoiler(StartingPosition startingPosition) {
	switch(startingPosition){
		case StartingPosition::BOILER:
			return PathLoader::loadPath("gearBoilerAuton_backupFromBoiler_boiler.csv", 1.0, (CORERobot::getAlliance() == RED));
			break;
		case StartingPosition::FEEDER:
			return PathLoader::loadPath("gearBoilerAuton_backupFromBoiler_feeder.csv", 1.0, (CORERobot::getAlliance() == RED));
			break;
		default:
			return AutonPaths::getReverseBoilerPath();
			//return PathLoader::loadPath("gearAuton_forward_center.csv", 1.0, (CORERobot::getAlliance() == RED));
			break;
	}
}

Path* GearBoilerHopperAuton::driveToHopper(StartingPosition startingPosition) {
	switch(startingPosition){
		case StartingPosition::BOILER:
			return PathLoader::loadPath("gearBoilerAuton_driveToHopper_boiler.csv", 1.0, (CORERobot::getAlliance() == RED));
			break;
		case StartingPosition::FEEDER:
			return PathLoader::loadPath("gearBoilerAuton_driveToHopper_feeder.csv", 1.0, (CORERobot::getAlliance() == RED));
			break;
		default:
			//return AutonPaths::getForwardHopperPath();
			return PathLoader::loadPath("gearAuton_forward_center.csv", 1.0, (CORERobot::getAlliance() == RED));
	}
}
