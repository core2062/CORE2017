#include "GearBoilerAuton.h"
#include "Actions.h"
#include "Robot.h"
#include "AutonPaths.h"

GearBoilerAuton::GearBoilerAuton(StartingPosition startingPosition) :
		COREAuton("Gear and Boiler Auton", 0.0){


}

void GearBoilerAuton::addNodes() {

	m_driveToPeg = new Node(15, new DriveWaypointAction(getForwardPath(Robot->getStartingPosition()), true));
	m_loadGearOnPeg = new Node(15, new LoadGearOntoPegAction());
	m_driveToBoiler = new Node(15, new DriveWaypointAction(getPathForBoiler(Robot->getStartingPosition()), false));
	m_dumpBallsInBoiler = new Node(15, new DumpBallsAction(false));
	m_shimmyHopper = new Node(15, new ShimmyAction(0.0, 0.0));

	addFirstNode(m_driveToPeg);
	m_driveToPeg->addNext(m_loadGearOnPeg);
	m_loadGearOnPeg->addNext(m_driveToBoiler);
	m_driveToBoiler->addNext(m_dumpBallsInBoiler);
	m_dumpBallsInBoiler->addNext(m_shimmyHopper);
	m_shimmyHopper->addNext(m_resetHopper);
}

Path * GearBoilerAuton::getForwardPath(StartingPosition startingPosition){
	switch(startingPosition){
	case StartingPosition::BOILER:
		return PathLoader::loadPath("gearBoilerAuton_forward_boiler.csv", 1.0, (CORERobot::getAlliance() == RED));
		break;
	default:
		//return AutonPaths::getForwardPegPath();
		return PathLoader::loadPath("gearAuton_forward_center.csv", 1.0, (CORERobot::getAlliance() == RED));
		break;
	}
}
Path* GearBoilerAuton::getPathForBoiler(StartingPosition startingPosition) {
	switch(startingPosition){
	case StartingPosition::BOILER:
		return PathLoader::loadPath("gearBoilerAuton_reverse_boiler.csv", 1.0, (CORERobot::getAlliance() == RED));
		break;
	default:
		//return AutonPaths::getForwardBoilerPath();
		return PathLoader::loadPath("gearAuton_forward_center.csv", 1.0, (CORERobot::getAlliance() == RED));
		break;
	}
}

