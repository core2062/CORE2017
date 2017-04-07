#include "GearBoilerAuton.h"
#include "Actions.h"
#include "Robot.h"
#include "AutonPaths.h"

GearBoilerAuton::GearBoilerAuton() :
		COREAuton("Gear and Boiler Auton", 0.0){}

void GearBoilerAuton::addNodes() {
	m_setLowGearPosition = new Node(10, new DriveShiftAction(GearPosition::LOW_GEAR));
	m_driveToPeg = new Node(4.5, new DriveWaypointAction(AutonPaths::getWallToPegPath(), true));
//	m_loadGearOnPeg = new Node(15, new LoadGearOntoPegAction());
	m_driveToBoiler = new Node(5, new DriveWaypointAction(AutonPaths::getPegToBoilerPath(), false), new LoadGearOntoPegAction());
	m_dumpBallsInBoiler = new Node(5, new DumpBallsAction(1.5));
	m_cross = new Node(9, new DriveWaypointAction(AutonPaths::getCrossFieldPath(), true));
	m_goHigh = new Node(2,  new DriveShiftAction(GearPosition::HIGH_GEAR));
	m_driveCross = new Node(5, new DriveDistanceAction(-1.0, 150, true));

//	m_shimmyHopper = new Node(1, new ShimmyAction(0.0, 0.0));

	addFirstNode(m_setLowGearPosition);
	m_setLowGearPosition->addNext(m_driveToPeg);
	m_driveToPeg->addNext(m_loadGearOnPeg);
	m_loadGearOnPeg->addNext(m_driveToBoiler);
	m_driveToBoiler->addNext(m_dumpBallsInBoiler);
	if (SmartDashboard::GetBoolean("Auto Cross Field", false)){
		m_dumpBallsInBoiler->addNext(m_goHigh);
		m_goHigh->addNext(m_cross);
		m_cross->addNext(m_driveCross);
	}
//	m_dumpBallsInBoiler->addNext(m_shimmyHopper);
//	m_shimmyHopper->addNext(m_resetHopper);
}

