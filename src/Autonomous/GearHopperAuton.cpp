#include <Autonomous/GearHopperAuton.h>
#include "Robot.h"
#include "Actions.h"
#include "AutonPaths.h"

GearHopperAuton::GearHopperAuton(StartingPosition startingPosition) :
	COREAuton("Gear and Hopper Auton", 0.0){

}
void GearHopperAuton::addNodes() {
	m_driveToPeg = new Node(15, new DriveWaypointAction(AutonPaths::getWallToPegPath()));
	m_loadGearOnPeg = new Node(15, new LoadGearOntoPegAction());
	m_backupFromPeg = new Node(15, new DriveWaypointAction(AutonPaths::getPegReversePath()));
	m_driveToHopper = new Node(15, new DriveWaypointAction(AutonPaths::getPegToHopperPath()));
	m_loadHopper = new Node(15, new HopperFlapAction());
	addFirstNode(m_driveToPeg);
	m_driveToPeg->addNext(m_loadGearOnPeg);
	m_loadGearOnPeg->addNext(m_backupFromPeg);
	m_backupFromPeg->addNext(m_driveToHopper);
	m_driveToHopper->addNext(m_loadHopper);
}

