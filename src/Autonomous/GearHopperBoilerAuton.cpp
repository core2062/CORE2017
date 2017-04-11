#include "Actions.h"
#include "Robot.h"
#include <Autonomous/GearHopperBoilerAuton.h>
#include "AutonPaths.h"

GearHopperBoilerAuton::GearHopperBoilerAuton() :
	COREAuton("Gear, Boiler, and Hopper Auton", 0.0){

	}

void GearHopperBoilerAuton::addNodes(){
	m_setLowGearPosition = new Node(10, new DriveShiftAction(GearPosition::LOW_GEAR));
	m_driveToPeg = new Node(5, new DriveWaypointAction(AutonPaths::getWallToPegPath(), true, .25, 100.0, true));
	m_driveToHopperA = new Node(5, new DriveWaypointAction(AutonPaths::getPegToHopperPathA(), false, .25, 500.0, false), new LoadGearOntoPegAction());
	m_driveToHopperB = new Node(5, new DriveWaypointAction(AutonPaths::getPegToHopperPathB(), true, .25, 500.0, false));
	m_loadHopper = new Node(3, new WaitAction(2.5));
	m_driveToBoiler = new Node(5, new DriveWaypointAction(AutonPaths::getHopperToBoilerPath(), false, .25, 250.0, false));
	m_dumpBallsInBoiler = new Node(8, new DumpBallsAction(8), new ShimmyAction(8));

	addFirstNode(m_setLowGearPosition);
	m_setLowGearPosition->addNext(m_driveToPeg);
	m_driveToPeg->addNext(m_driveToHopperA);
	m_driveToHopperA->addNext(m_driveToHopperB);
	m_driveToHopperB->addNext(m_loadHopper);
	m_loadHopper->addNext(m_driveToBoiler);
	m_driveToBoiler->addNext(m_dumpBallsInBoiler);
	}

