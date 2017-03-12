#include "Robot.h"
#include "GearOnlyAuton.h"
#include "Actions.h"
#include "AutonPaths.h"

using namespace CORE;

GearOnlyAuton::GearOnlyAuton(StartingPosition startingPosition) :
		COREAuton("Gear Only", 0.0){

}
void GearOnlyAuton::addNodes() {
	m_driveToPeg = new Node(15, new DriveWaypointAction(AutonPaths::getWallToPegPath(), true));
	m_loadGearOnPeg = new Node(15, new LoadGearOntoPegAction());
	m_reverseDrive = new Node(15, new DriveWaypointAction(AutonPaths::getPegReversePath()));
	addFirstNode(m_driveToPeg);
	m_driveToPeg->addNext(m_loadGearOnPeg);
	m_loadGearOnPeg->addNext(m_reverseDrive);
}
