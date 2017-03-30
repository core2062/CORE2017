#include "HopperBoilerAuton.h"
#include "Robot.h"
#include "Actions.h"
#include "AutonPaths.h"

using namespace CORE;

HopperBoilerAuton::HopperBoilerAuton(StartingPosition startingPosition):
	COREAuton("Hopper and Boiler Auton", 0.0),
	m_shimmyScale("Shimmy Scale", 0.0){

	}

void HopperBoilerAuton::addNodes(){
	m_setLowGearPosition = new Node(10, new DriveShiftAction(GearPosition::LOW_GEAR));
	m_driveToHopper = new Node(10, new DriveWaypointAction(AutonPaths::getWallToHopperPath()));
	m_loadHopper = new Node(3, new WaitAction(2.5));
	m_backupFromHopper = new Node(15, new DriveWaypointAction(AutonPaths::getReverseHopperPath()));
	m_driveToBoiler = new Node(15, new DriveWaypointAction(AutonPaths::getHopperToBoilerPath()));
	m_dumpBallsInBoiler = new Node(4, new DumpBallsAction(1.5));
	m_backupFromBoiler = new Node(10, new DriveWaypointAction(AutonPaths::))

	addFirstNode(m_setLowGearPosition);
	m_setLowGearPosition->addNext(m_driveToHopper);
	m_driveToHopper->addNext(m_loadHopper);
	m_loadHopper->addNext(m_backupFromHopper);
	m_backupFromHopper->addNext(m_driveToBoiler);
	m_driveToBoiler->addNext(m_dumpBallsInBoiler);
	m_dumpBallsInBoiler->addNext(m_shimmyHopper);
	m_shimmyHopper->addNext(m_resetHopper);
	m_resetHopper->addNext(m_backupFromBoiler);
	m_backupFromBoiler->addNext(m_driveToPeg);


}


