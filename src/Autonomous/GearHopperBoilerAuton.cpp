#include "Actions.h"
#include "Robot.h"
#include <Autonomous/GearHopperBoilerAuton.h>

GearHopperBoilerAuton::GearHopperBoilerAuton() :
	COREAuton("Gear, Boiler and Hopper Auton", &m_driveToPeg, true),
	m_driveToPeg(new DriveWaypointAction(getPathForPeg(Robot->getStartingPosition()))),
	m_loadGearOnPeg(new LoadGearOntoPegAction()),
	m_backupFromPeg(new DriveWaypointAction(backupFromPeg())),
	m_driveToHopper(new DriveWaypointAction(driveToHopper())),
	m_loadHopper(new HopperFlapAction()),
	m_backupFromHopper(new DriveWaypointAction(backupFromHopper())),
	m_driveToBoiler(new DriveWaypointAction(driveToBoiler())),
	m_dumpBallsInBoiler(new DumpBallsAction(false)),
	m_shimmyHopper(new ShimmyAction(0.0, 0.0)),
	m_resetHopper(new DumpBallsAction(true)),
	m_shimmyScale("Shimmy Scale", 0.0){

	}

void GearHopperBoilerAuton::addNodes(){
	m_driveToPeg.addNext(&m_loadGearOnPeg),
	m_loadGearOnPeg.addNext(&m_backupFromPeg),
	m_backupFromPeg.addNext(&m_driveToHopper),
	m_driveToHopper.addNext(&m_loadHopper),
	m_loadHopper.addNext(&m_backupFromHopper),
	m_backupFromHopper.addNext(&m_driveToBoiler),
	m_driveToBoiler.addNext(&m_dumpBallsInBoiler),
	m_dumpBallsInBoiler.addNext(&m_shimmyHopper),
	m_shimmyHopper.addNext(&m_resetHopper);
	}

Path* GearHopperBoilerAuton::getPathForPeg(StartingPosition startingPosition){
	return new Path({{{0,0},0}, {{1,1},1}});
	}

Path * GearHopperBoilerAuton::backupFromPeg(){
	return new Path({{{0,0},0}, {{1,1},1}});
	}

Path * GearHopperBoilerAuton::driveToHopper(){
	return new Path({{{0,0},0}, {{1,1},1}});
	}

Path* GearHopperBoilerAuton::backupFromHopper() {
	return new Path({{{0,0},0}, {{1,1},1}});
	}

Path* GearHopperBoilerAuton::driveToBoiler() {
	return new Path({{{0,0},0}, {{1,1},1}});
	}
