#include "2GearAuton.h"
#include "Actions.h"
#include "Robot.h"
#include "AutonPaths.h"

TwoGearAuton::TwoGearAuton() :
	COREAuton("Two Gear Auton", 0.0){}

void TwoGearAuton::addNodes() {
	m_driveA = new Node(7, new DriveWaypointAction(AutonPaths::getWallToPegPath(), true, .25, 100.0, true), new DriveShiftAction(GearPosition::LOW_GEAR));
	m_driveB = new Node(10, new DriveWaypointAction(	PathLoader::loadPath("2gearA.csv", 1.0,
			(CORERobot::getAlliance() == CORERobot::RED)), false), new LoadGearOntoPegAction());
	m_driveC = new Node(10, new DriveWaypointAction(	PathLoader::loadPath("2gearB.csv", 1.0,
			(CORERobot::getAlliance() == CORERobot::RED)), true), new PickupGearAction());
	m_driveD = new Node(10, new DriveWaypointAction(	PathLoader::loadPath("2gearC.csv", 1.0,
			(CORERobot::getAlliance() == CORERobot::RED)), false));
	m_driveE = new Node(10, new DriveWaypointAction(	PathLoader::loadPath("2gearD.csv", 1.0,
			(CORERobot::getAlliance() == CORERobot::RED)), true));

	addFirstNode(m_driveA);
	m_driveA->addNext(m_driveB);
	m_driveB->addNext(m_driveC);
	m_driveC->addNext(m_driveD);
	m_driveD->addNext(m_driveE);
}
