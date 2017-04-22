#include "AntiTitaniumAuton.h"
#include "Robot.h"
#include "Actions.h"
#include "AutonPaths.h"

AntiTitaniumAuton::AntiTitaniumAuton() :
	COREAuton("Def Legal Auton", 0.0){
}

void AntiTitaniumAuton::addNodes() {
	m_setLowGear = new Node(1, new DriveShiftAction(GearPosition::LOW_GEAR));
	m_approachPeg = new Node(5, new DriveWaypointAction(AutonPaths::getApproachPegPath(), true, .25, 125, true));
	m_waitForVision = new Node(10, new WaitAction(.25));
	m_driveOnPeg = new Node(7, new VisionPathAction());
	m_loadGearOnPeg = new Node(1.5, new LoadGearOntoPegAction(), new WaitAction(.5));
	m_reverseDrive = new Node(15, new DriveWaypointAction(AutonPaths::getPegReversePath()));
	m_prepCrossA = new Node(12, new DriveWaypointAction(AutonPaths::getPegToCrossPathA(), false, .25, 150.0, false));
	m_prepCrossB = new Node(12, new DriveWaypointAction(AutonPaths::getPegToCrossPathB(), true, .25, 1500.0, false));
	m_cross = new Node(6, new DriveDistanceAction(-1.0, 100, false));

	addFirstNode(m_setLowGear);
	m_setLowGear->addNext(m_approachPeg);
	m_approachPeg->addNext(m_waitForVision);
	m_waitForVision->addNext(m_driveOnPeg);
	m_driveOnPeg->addNext(m_loadGearOnPeg);
	if (SmartDashboard::GetBoolean("Auto Cross Field", false)){
		m_loadGearOnPeg->addNext(m_prepCrossA);
		m_prepCrossA->addNext(m_prepCrossB);
		m_prepCrossB->addNext(m_cross);
	} else {
		m_loadGearOnPeg->addNext(m_reverseDrive);
	}
}
