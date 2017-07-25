#include "Actions.h"
#include "Robot.h"
#include <Autonomous/GearHopperBoilerAuton.h>
#include "AutonPaths.h"

GearHopperBoilerAuton::GearHopperBoilerAuton() :
	COREAuton("Gear, Boiler, and Hopper Auton", 0.0){

	}

void GearHopperBoilerAuton::addNodes(){
	m_approachPeg = new Node(5, new DriveWaypointAction(AutonPaths::getApproachPegPath(), true, .25, 125, true));
	m_waitForVision = new Node(10, new WaitAction(.25));
	m_driveOnPeg = new Node(7, new VisionPathAction());

	m_driveToPeg = new Node(5, new DriveWaypointAction(AutonPaths::getWallToPegPath(), true, .25, 100.0, true));
	m_loadGearOnPeg = new Node(15, new LoadGearOntoPegAction(), new WaitAction(.5));

	m_driveToHopperA = new Node(5, new DriveWaypointAction(AutonPaths::getPegToHopperPathA(), false, .25, 500.0, false));
	m_turnToHopper = new Node(3, new TurnAngleAction(Rotation2d::fromDegrees(-90 * CORERobot::getAlliance()), 10));
	m_driveToHopperB = new Node(5, new DriveWaypointAction(AutonPaths::getPegToHopperPathB(), true, .25, 500.0, false));

	m_loadHopper = new Node(3, new WaitAction(2.5));
	m_driveToBoiler = new Node(5, new DriveWaypointAction(AutonPaths::getHopperToBoilerPath(), false, .25, 250.0, false));
	m_dumpBallsInBoiler = new Node(8, new DumpBallsAction(8));

	if (SmartDashboard::GetBoolean("Use Vision", false)){
		addFirstNode(m_approachPeg);
		m_approachPeg->addNext(m_waitForVision);
		m_waitForVision->addNext(m_driveOnPeg);
		m_driveOnPeg->addNext(m_loadGearOnPeg);
	} else {
		addFirstNode(m_driveToPeg);
		m_driveToPeg->addNext(m_loadGearOnPeg);
	}

	m_loadGearOnPeg->addNext(m_driveToHopperA);

	m_driveToHopperA->addNext(m_driveToHopperB);
	m_driveToHopperB->addNext(m_loadHopper);
	m_loadHopper->addNext(m_driveToBoiler);
	m_driveToBoiler->addNext(m_dumpBallsInBoiler);
	}

