#include <Autonomous/GearHopperAuton.h>
#include "Robot.h"
#include "Actions.h"

GearHopperAuton::GearHopperAuton(StartingPosition startingPosition) :
	COREAuton("Gear and Hopper Auton", 0.0){

}
void GearHopperAuton::addNodes() {
	m_driveToPeg = new Node(15, new DriveWaypointAction(PathLoader::loadPath("drivetopeg.csv", 1.0, true, true)));
	m_loadGearOnPeg = new Node(15, new LoadGearOntoPegAction());
	m_backupFromPeg = new Node(15, new DriveWaypointAction(PathLoader::loadPath("backupfrompeg.csv", 1.0, true, true)));
	m_driveToHopper = new Node(15, new DriveWaypointAction(PathLoader::loadPath("drivetohopper.csv", 1.0, true, true)));
	m_loadHopper = new Node(15, new HopperFlapAction());
	addFirstNode(m_driveToPeg);
	m_driveToPeg->addNext(m_loadGearOnPeg);
	m_loadGearOnPeg->addNext(m_backupFromPeg);
	m_backupFromPeg->addNext(m_driveToHopper);
	m_driveToHopper->addNext(m_loadHopper);
}

Path* GearHopperAuton::getPathForPeg(StartingPosition startingPosition) {
	return new Path({{{0,0},0}, {{1,1},1}});
}

Path* GearHopperAuton::backupFromPeg() {
	return new Path({{{0,0},0}, {{1,1},1}});
}

Path* GearHopperAuton::driveToHopper() {
	return new Path({{{0,0},0}, {{1,1},1}});
}
