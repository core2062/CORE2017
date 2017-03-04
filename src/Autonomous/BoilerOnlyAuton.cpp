#include "Robot.h"
#include "BoilerOnlyAuton.h"
#include "Actions.h"

using namespace CORE;

BoilerOnlyAuton::BoilerOnlyAuton() :
		COREAuton("Boiler Only", &m_driveToBoiler, true),
		m_driveToBoiler(new DriveWaypointAction(getPathFor(Robot->getStartingPosition()))),
		m_dumpBallsInBoiler(new DumpBallsAction(false)),
		m_shimmyHopper(new ShimmyAction(0.0, 0.0)),
		m_resetHopper(new DumpBallsAction(true)),
		m_shimmyScale("Shimmy Scale", 0.0){
	//TODO: Add functionality for Wall/middle paths
}


void BoilerOnlyAuton::addNodes() {
	m_driveToBoiler.addNext(&m_dumpBallsInBoiler);
	m_dumpBallsInBoiler.addNext(&m_shimmyHopper);
	m_shimmyHopper.addNext(&m_resetHopper);
}

Path * BoilerOnlyAuton::getPathFor(int startingPosition) {
	return new Path({{{0,0},0}, {{1,1},1}});
	//TODO: Replace with code that reads the path from the csv file
}
