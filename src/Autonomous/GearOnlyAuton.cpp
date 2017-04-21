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
	m_setLowGear = new Node(1, new DriveShiftAction(GearPosition::LOW_GEAR));
//	if( Robot->getStartingPosition() != StartingPosition::CENTER){
//		m_driveForward = new Node( 3, new DriveDistanceAction(-1.0, feederForwardDist.Get()));
//		m_turnToPeg = new Node( 3, new TurnAngleAction(Rotation2d::fromDegrees(-60 * Robot->getAlliance()), 5));
		m_driveForward = new Node( 5, new DriveWaypointAction(AutonPaths::getWallToPegPath(), true, .25, 125, true));
//	}
//	if( Robot->getStartingPosition() == StartingPosition::BOILER){
//		m_driveForward = new Node( 3, new DriveDistanceAction(-1.0, boilerForwardDist.Get()));
//		m_turnToPeg = new Node( 3, new TurnAngleAction(Rotation2d::fromDegrees(60 * Robot->getAlliance()), 5));
//	}
	m_driveToPeg = new Node(7, new VisionAlignGearAction());
	m_loadGearOnPeg = new Node(1.5, new LoadGearOntoPegAction(), new WaitAction(.5));
	m_reverseDrive = new Node(15, new DriveWaypointAction(AutonPaths::getPegReversePath()));
	m_prepCrossA = new Node(12, new DriveWaypointAction(AutonPaths::getPegToCrossPathA(), false, .25, 150.0, false));
	m_prepCrossB = new Node(12, new DriveWaypointAction(AutonPaths::getPegToCrossPathB(), true, .25, 150.0, false));
	m_cross = new Node(6, new DriveDistanceAction(-1.0, 100, false));

	addFirstNode(m_setLowGear);
//	if(m_driveForward != nullptr){
		m_setLowGear->addNext(m_driveForward);
//		m_driveForward->addNext(m_driveToPeg);
//	} else {
//		m_setLowGear->addNext(m_driveToPeg);
//	}

	m_driveForward->addNext(m_loadGearOnPeg);

	if (SmartDashboard::GetBoolean("Auto Cross Field", false)){
		m_loadGearOnPeg->addNext(m_prepCrossA);
		m_prepCrossA->addNext(m_prepCrossB);
		m_prepCrossB->addNext(m_cross);
	} else {
		m_loadGearOnPeg->addNext(m_reverseDrive);
	}
}
