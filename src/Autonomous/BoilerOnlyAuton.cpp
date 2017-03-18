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
	m_setLowGearPosition = new Node (10, new DriveShiftAction(GearPosition::LOW_GEAR));
	m_driveToBoiler = new Node(10, new DriveWaypointAction(AutonPaths::getWallToBoilerPath()));
	m_dumpBallsInBoiler = new Node(15, new DumpBallsAction(false)); //Hardcoded value for now, need to pass in a reset bool.
	m_shimmyHopper = new Node(15, new ShimmyAction(0.0, 0.0));
	addFirstNode(m_setLowGearPosition);
	m_setLowGearPosition->addNext(m_driveToBoiler);
	m_driveToBoiler->addNext(m_dumpBallsInBoiler);
	m_dumpBallsInBoiler->addNext(m_shimmyHopper);
	m_shimmyHopper->addNext(m_resetHopper);
}


