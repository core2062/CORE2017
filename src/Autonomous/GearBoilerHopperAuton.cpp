#include "Actions.h"
#include "Robot.h"
#include <Autonomous/GearBoilerHopperAuton.h>
#include "AutonPaths.h"

GearBoilerHopperAuton::GearBoilerHopperAuton(StartingPosition startingPosition) :
	COREAuton("Gear and Hopper Auton", 0.0){


}

void GearBoilerHopperAuton::addNodes() {
	m_setLowGearPosition = new Node(10, new DriveShiftAction(GearPosition::LOW_GEAR));
	m_driveToPeg = new Node(15, new DriveWaypointAction(AutonPaths::getWallToPegPath()));
	m_loadGearOnPeg = new Node(15, new LoadGearOntoPegAction());
	m_backupFromPeg = new Node(15, new DriveWaypointAction(AutonPaths::getPegReversePath()));
	m_driveToBoiler = new Node(15, new DriveWaypointAction(AutonPaths::getPegToBoilerPath()));
	m_dumpBallsInBoiler = new Node(15, new DumpBallsAction(false));
	m_shimmyHopper = new Node(15, new ShimmyAction(0.0, 0.0));
//	m_backupFromBoiler = new Node(15, new DriveWaypointAction(AutonPaths::backupFromBoilerPath()));
	m_driveToHopper = new Node(15, new DriveWaypointAction(AutonPaths::getBoilerToHopperPath()));
	m_loadHopper = new Node(3, new HopperFlapAction());

	addFirstNode(m_setLowGearPosition);
	m_setLowGearPosition->addNext(m_driveToPeg);
	m_driveToPeg->addNext(m_loadGearOnPeg),
	m_loadGearOnPeg->addNext(m_backupFromPeg),
	m_backupFromPeg->addNext(m_driveToBoiler),
	m_driveToBoiler->addNext(m_dumpBallsInBoiler),
	m_dumpBallsInBoiler->addNext(m_shimmyHopper),
	m_shimmyHopper->addNext(m_backupFromBoiler),
	m_backupFromBoiler->addNext(m_driveToHopper),
	m_driveToHopper->addNext(m_loadHopper);

}

