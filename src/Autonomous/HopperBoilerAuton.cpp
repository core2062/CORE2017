#include "HopperBoilerAuton.h"
#include "Robot.h"
#include "Actions.h"
#include "AutonPaths.h"

using namespace CORE;

HopperBoilerAuton::HopperBoilerAuton():
	COREAuton("Hopper and Boiler Auton", 0.0),
	m_shimmyScale("Shimmy Scale", 0.0){

	}

void HopperBoilerAuton::addNodes(){
	m_setLowGearPosition = new Node(10, new DriveShiftAction(GearPosition::LOW_GEAR));
	m_driveToHopper = new Node(10, new DriveWaypointAction(AutonPaths::getWallToHopperPath(),true, .25, 290.0, false));
	m_loadHopper = new Node(3, new /*ShimmyAction(2.5, -1.0)*/WaitAction(4.5));
	m_driveToBoiler = new Node(15, new DriveWaypointAction(AutonPaths::getHopperToBoilerPath()));
	//m_dumpBallsInBoiler = new Node(4, new DumpBallsAction(2.5), new ShimmyAction(2.5));
	m_driveToPeg = new Node(10, new DriveWaypointAction(AutonPaths::getBoilerToPegPath(), true));

	addFirstNode(m_setLowGearPosition);
	m_setLowGearPosition->addNext(m_driveToHopper);
	m_driveToHopper->addNext(m_loadHopper);
	m_loadHopper->addNext(m_driveToBoiler);
	m_driveToBoiler->addNext(m_dumpBallsInBoiler);
//	m_dumpBallsInBoiler->addNext(m_shimmyHopper);
//	m_shimmyHopper->addNext(m_resetHopper);



}


