#include "GearBoilerAuton.h"
#include "Actions.h"
#include "Robot.h"
#include "AutonPaths.h"

GearBoilerAuton::GearBoilerAuton() :
		COREAuton("Gear and Boiler Auton", 0.0){


}

void GearBoilerAuton::addNodes() {

	m_driveToPeg = new Node(3.5, new DriveWaypointAction(GearOnlyAuton::getForwardPegPath(Robot->getStartingPosition()), true));
	m_loadGearOnPeg = new Node(15, new LoadGearOntoPegAction());
	m_driveToBoiler = new Node(5, new DriveWaypointAction(getPathForBoiler(Robot->getStartingPosition()), false));
	m_dumpBallsInBoiler = new Node(1, new DumpBallsAction(false));
	m_shimmyHopper = new Node(1, new ShimmyAction(0.0, 0.0));

	addFirstNode(m_driveToPeg);
	m_driveToPeg->addNext(m_loadGearOnPeg);
	m_loadGearOnPeg->addNext(m_driveToBoiler);
	m_driveToBoiler->addNext(m_dumpBallsInBoiler);
	m_dumpBallsInBoiler->addNext(m_shimmyHopper);
	m_shimmyHopper->addNext(m_resetHopper);
}

Path* GearBoilerAuton::getPathForBoiler(StartingPosition startingPosition) {
	switch(startingPosition){
	case StartingPosition::BOILER:
		return PathLoader::loadPath("gearBoilerAuton_reverse_boiler.csv", 1.0, (CORERobot::getAlliance() == RED));
		break;
	default:
		//return AutonPaths::getForwardBoilerPath();
		return PathLoader::loadPath("gearBoilerAuton_reverse_center.csv", 1.0, (CORERobot::getAlliance() == RED));
		break;
	}
}

