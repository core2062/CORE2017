#include "Actions.h"
#include "Robot.h"
#include <Autonomous/GearBoilerHopper.h>

GearBoilerHopper::GearBoilerHopper(StartingPosition startingPosition) :
	COREAuton("Gear and Hopper Auton", 0.0){


}

void GearBoilerHopper::addNodes() {
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

Path* GearBoilerHopper::getPathForPeg(int startingPosition) {
	return new Path({{{0,0},0}, {{1,1},1}});
}

Path* GearBoilerHopper::backupFromPeg() {
	return new Path({{{0,0},0}, {{1,1},1}});
}

Path* GearBoilerHopper::driveToBoiler() {
	return new Path({{{0,0},0}, {{1,1},1}});
}

Path* GearBoilerHopper::backupFromBoiler() {
	return new Path({{{0,0},0}, {{1,1},1}});
}

Path* GearBoilerHopper::driveToHopper() {
	return new Path({{{0,0},0}, {{1,1},1}});
}
