#include <Autonomous/GearHopperAuton.h>
#include "Robot.h"
#include "Actions.h"

GearHopperAuton::GearHopperAuton() :
	COREAuton("Gear and Hopper Auton", &m_driveToPeg, true),
	m_driveToPeg(new DriveWaypointAction(getPathForPeg(Robot->getStartingPosition()))),
	m_loadGearOnPeg(new LoadGearOntoPegAction()),
	m_backupFromPeg(new DriveWaypointAction(backupFromPeg())),
	m_driveToHopper(new DriveWaypointAction(driveToHopper())),
	m_loadHopper(new HopperFlapAction()){

}
void GearHopperAuton::addNodes() {
	m_driveToPeg.addNext(&m_loadGearOnPeg);
	m_loadGearOnPeg.addNext(&m_backupFromPeg);
	m_backupFromPeg.addNext(&m_driveToHopper);
	m_driveToHopper.addNext(&m_loadHopper);
}

Path* GearHopperAuton::getPathForPeg(int startingPosition) {
	return new Path({{{0,0},0}, {{1,1},1}});
}

Path* GearHopperAuton::backupFromPeg() {
	return new Path({{{0,0},0}, {{1,1},1}});
}

Path* GearHopperAuton::driveToHopper() {
	return new Path({{{0,0},0}, {{1,1},1}});
}
