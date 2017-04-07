#include "Robot.h"
#include "GearOnlyAuton.h"
#include "Actions.h"
#include "AutonPaths.h"

using namespace CORE;

GearOnlyAuton::GearOnlyAuton(StartingPosition startingPosition) :
		COREAuton("Gear Only", 0.0){

}
void GearOnlyAuton::addNodes() {
	m_setLowGearPosition = new Node(1, new DriveShiftAction(GearPosition::LOW_GEAR));
	m_driveToPeg = new Node(7, new DriveWaypointAction(AutonPaths::getWallToPegPath(), true));
//	m_loadGearOnPeg = new Node(1.5, new LoadGearOntoPegAction());
	m_reverseDrive = new Node(15, new DriveWaypointAction(AutonPaths::getPegReversePath()),  new LoadGearOntoPegAction());
	m_prepCrossA = new Node(12, new DriveWaypointAction(AutonPaths::getPegToCrossPathA(), false),  new LoadGearOntoPegAction());
	m_prepCrossB = new Node(12, new DriveWaypointAction(AutonPaths::getPegToCrossPathB(), true));
	m_cross = new Node(6, new DriveDistanceAction(1.0, 180, true));

	addFirstNode(m_setLowGearPosition);
	m_setLowGearPosition->addNext(m_driveToPeg);
	m_driveToPeg->addNext(m_loadGearOnPeg);

	if (SmartDashboard::GetBoolean("Auto Cross Field", false)){
		m_loadGearOnPeg->addNext(m_prepCrossA);
		m_prepCrossA->addNext(m_prepCrossB);
		m_prepCrossB->addNext(m_cross);
	} else {
		m_loadGearOnPeg->addNext(m_reverseDrive);
	}
}
