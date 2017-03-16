#include "GearBoilerAuton.h"
#include "Actions.h"
#include "Robot.h"
#include "AutonPaths.h"

GearBoilerAuton::GearBoilerAuton() :
		COREAuton("Gear and Boiler Auton", 0.0){}

void GearBoilerAuton::addNodes() {

	m_driveToPeg = new Node(4.5, new DriveWaypointAction(AutonPaths::getWallToPegPath(), true));
	m_loadGearOnPeg = new Node(15, new LoadGearOntoPegAction());
	m_driveToBoiler = new Node(5, new DriveWaypointAction(AutonPaths::getPegToBoilerPath(), false));
	m_dumpBallsInBoiler = new Node(5, new DumpBallsAction(1.5));
//	m_shimmyHopper = new Node(1, new ShimmyAction(0.0, 0.0));

	addFirstNode(m_driveToPeg);
	m_driveToPeg->addNext(m_loadGearOnPeg);
	m_loadGearOnPeg->addNext(m_driveToBoiler);
	m_driveToBoiler->addNext(m_dumpBallsInBoiler);
//	m_dumpBallsInBoiler->addNext(m_shimmyHopper);
//	m_shimmyHopper->addNext(m_resetHopper);
}

