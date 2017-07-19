#include "Robot.h"
#include "GearOnlyAuton.h"
#include "Actions.h"
#include "AutonPaths.h"

using namespace CORE;

GearOnlyAuton::GearOnlyAuton(StartingPosition startingPosition) :
		COREAuton("Gear Only", 0.0),
		feederForwardDist("Feeder Forward Distance", 80),
		boilerForwardDist("Boiler Forward Distance", 100)
{}

void GearOnlyAuton::addNodes() {

	switch(Robot->getStartingPosition()){
		case StartingPosition::BOILER:
				m_turnToPeg = new Node (3, new TurnAngleAction(Rotation2d::fromDegrees(60.0 * CORERobot::getAlliance()), 1, 5));
			break;
		case StartingPosition::FEEDER:
			m_turnToPeg = new Node (3, new TurnAngleAction(Rotation2d::fromDegrees(-60.0 * CORERobot::getAlliance()), 1, 5));
			break;
		case StartingPosition::CENTER:
			m_turnToPeg = new Node (3, new TurnAngleAction(Rotation2d::fromDegrees(0), 1, 5));
			break;
	}

	m_approachPeg = new Node(5, new DriveWaypointAction(AutonPaths::getApproachPegPath(), true, .25, 125, true));
	m_waitForVision = new Node(10, new WaitAction(2.25));
	m_driveOnPeg = new Node(7, new VisionPathAction());

	m_driveToPeg = new Node(7, new DriveWaypointAction(AutonPaths::getWallToPegPath(), true, .25, 125, true));
	m_loadGearOnPeg = new Node(1.5, new LoadGearOntoPegAction(), new WaitAction(.5));
	m_reverseDrive = new Node(15, new DriveWaypointAction(AutonPaths::getPegReversePath()));
	m_prepCrossA = new Node(12, new DriveWaypointAction(AutonPaths::getPegToCrossPathA(), false, .25, 150.0, false));
	m_prepCrossB = new Node(12, new DriveWaypointAction(AutonPaths::getPegToCrossPathB(), true, .25, 1500.0, false));
	m_cross = new Node(6, new DriveDistanceAction(-1.0, 5));

	if (SmartDashboard::GetBoolean("Use Vision", false)){
		addFirstNode(m_approachPeg);
		if(	SmartDashboard::GetBoolean("Vision Set Heading", false)){
			m_approachPeg->addNext(m_turnToPeg);
			m_turnToPeg->addNext(m_waitForVision);
		} else {
			m_approachPeg->addNext(m_waitForVision);
		}
		m_waitForVision->addNext(m_driveOnPeg);
		m_driveOnPeg->addNext(m_loadGearOnPeg);
	} else {
		addFirstNode(m_driveToPeg);
		m_driveToPeg->addNext(m_loadGearOnPeg);
	}

	if (SmartDashboard::GetBoolean("Auto Cross Field", false)){
		m_loadGearOnPeg->addNext(m_prepCrossA);
		m_prepCrossA->addNext(m_prepCrossB);
		m_prepCrossB->addNext(m_cross);
	} else {
		m_loadGearOnPeg->addNext(m_reverseDrive);
	}
}
