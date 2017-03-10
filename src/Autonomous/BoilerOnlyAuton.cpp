#include "Robot.h"
#include "BoilerOnlyAuton.h"
#include "Actions.h"
#include "AutonPaths.h"
using namespace CORE;

BoilerOnlyAuton::BoilerOnlyAuton() :
		COREAuton("Boiler Only", 0.0),
	m_shimmyScale("Shimmy Scale", 0.0){
	//TODO: Add functionality for Wall/middle paths
}


void BoilerOnlyAuton::addNodes() {
	m_driveToBoiler = new Node(10, new DriveWaypointAction(PathLoader::loadPath("drivetoboiler.csv", 1.0, true, true)));
	m_dumpBallsInBoiler = new Node(15, new DumpBallsAction(false)); //Hardcoded value for now, need to pass in a reset bool.
	m_shimmyHopper = new Node(15, new ShimmyAction(0.0, 0.0));
	addFirstNode(m_driveToBoiler);
	m_driveToBoiler->addNext(m_dumpBallsInBoiler);
	m_dumpBallsInBoiler->addNext(m_shimmyHopper);
	m_shimmyHopper->addNext(m_resetHopper);
}

Path * BoilerOnlyAuton::getPathFor(StartingPosition startingPosition) {
	PathLoader::loadPath("BoilerOnlyAuton_reverse_boiler.csv", 1.0, (CORERobot::getAlliance() == RED));
}
