#include "Actions.h"
#include "Robot.h"
#include <Autonomous/GearHopperBoilerAuton.h>

GearHopperBoilerAuton::GearHopperBoilerAuton() :
	COREAuton("Gear, Boiler and Hopper Auton", 0.0),
	m_shimmyScale("Shimmy Scale", 0.0){

	}

void GearHopperBoilerAuton::addNodes(){
	m_driveToPeg = new Node(15, new DriveWaypointAction(PathLoader::loadPath("drivetopeg.csv", 1.0, true, true)));
	m_loadGearOnPeg = new Node(1, new LoadGearOntoPegAction());
	m_backupFromPeg = new Node(15, new DriveWaypointAction(PathLoader::loadPath("backupfrompeg.csv", 1.0, true, true)));
	m_driveToHopper = new Node(15, new DriveWaypointAction(PathLoader::loadPath("drivetohopper.csv", 1.0, true, true)));
	m_loadHopper = new Node(3, new HopperFlapAction());
	m_backupFromHopper = new Node(15, new DriveWaypointAction(PathLoader::loadPath("backupfromhopper.csv", 1.0, true, true)));
	m_driveToBoiler = new Node(15, new DriveWaypointAction(PathLoader::loadPath("drivetoboiler.csv", 1.0, true, true)));
	m_dumpBallsInBoiler = new Node(4, new DumpBallsAction(true));
	m_shimmyHopper = new Node(3, new ShimmyAction(0.0, 0.0));
	m_resetHopper = new Node(3, new DumpBallsAction(true));
	addFirstNode(m_driveToPeg);
	m_driveToPeg->addNext(m_loadGearOnPeg),
	m_loadGearOnPeg->addNext(m_backupFromPeg),
	m_backupFromPeg->addNext(m_driveToHopper),
	m_driveToHopper->addNext(m_loadHopper),
	m_loadHopper->addNext(m_backupFromHopper),
	m_backupFromHopper->addNext(m_driveToBoiler),
	m_driveToBoiler->addNext(m_dumpBallsInBoiler),
	m_dumpBallsInBoiler->addNext(m_shimmyHopper),
	m_shimmyHopper->addNext(m_resetHopper);
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
