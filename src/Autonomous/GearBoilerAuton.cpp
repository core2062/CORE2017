#include "GearBoilerAuton.h"
#include "Actions.h"
#include "Robot.h"
#include "AutonPaths.h"

GearBoilerAuton::GearBoilerAuton() :
		COREAuton("Gear and Boiler Auton", 0.0){}

void GearBoilerAuton::addNodes() {
	m_approachPeg = new Node(5, new DriveWaypointAction(AutonPaths::getApproachPegPath(), true, .25, 125, true));
	m_waitForVision = new Node(10, new WaitAction(.25));
	m_driveOnPeg = new Node(7, new VisionPathAction());

	m_driveToPeg = new Node(6.5, new DriveWaypointAction(AutonPaths::getWallToPegPath(), true, .25, 500, false));
	m_loadGearOnPeg = new Node(15, new LoadGearOntoPegAction(), new WaitAction(.5));
	m_driveToBoiler = new Node(10, new DriveWaypointAction(AutonPaths::getPegToBoilerPath(), false, .25, 250, true));
	m_dumpBallsInBoiler = new Node(5, new DumpBallsAction(1.5));
	m_cross = new Node(9, new DriveWaypointAction(AutonPaths::getCrossFieldPath(), true, .25, 2500, false));
	m_driveCross = new Node(5, new DriveDistanceAction(-1.0, 5));

	if (SmartDashboard::GetBoolean("Use Vision", false)){
		addFirstNode(m_approachPeg);
		m_approachPeg->addNext(m_waitForVision);
		m_waitForVision->addNext(m_driveOnPeg);
		m_driveOnPeg->addNext(m_loadGearOnPeg);
	} else {
		addFirstNode(m_driveToPeg);
		m_driveToPeg->addNext(m_loadGearOnPeg);
	}

	m_loadGearOnPeg->addNext(m_driveToBoiler);
	m_driveToBoiler->addNext(m_dumpBallsInBoiler);

	if (SmartDashboard::GetBoolean("Auto Cross Field", false)){
		m_dumpBallsInBoiler->addNext(m_cross);
		m_cross->addNext(m_driveCross);
	}
}

