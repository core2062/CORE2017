#include "2GearAuton.h"
#include "Actions.h"
#include "Robot.h"
#include "AutonPaths.h"

TwoGearAuton::TwoGearAuton() :
	COREAuton("Two Gear Auton", 0.0){}

void TwoGearAuton::addNodes() {
	m_driveA = new Node(7, new DriveWaypointAction(AutonPaths::getWallToPegPath(), true, .25, 125.0, true), new DriveShiftAction(GearPosition::LOW_GEAR));
	m_dropA = new Node(2, new LoadGearOntoPegAction(), new WaitAction(.25));
	m_driveB = new Node(10, new DriveWaypointAction(	PathLoader::loadPath("2gearA.csv", 1.0,
			(CORERobot::getAlliance() == CORERobot::RED)), false, .25, 2500.0, false));
	m_turnA = new Node(3, new TurnAngleAction(Rotation2d::fromDegrees(-135), 15));
	m_driveC = new Node(10, new DriveWaypointAction(	PathLoader::loadPath("2gearB.csv", 1.0,
			(CORERobot::getAlliance() == CORERobot::RED)), true, .25, 2500.0, false), new PickupGearAction());
	m_driveD = new Node(10, new DriveWaypointAction(	PathLoader::loadPath("2gearC.csv", 1.0,
			(CORERobot::getAlliance() == CORERobot::RED)), false, 25, 2500.0, false), new PickupGearAction(true));
	m_turnB = new Node(3, new TurnAngleAction(Rotation2d::fromDegrees(0), 10));
	m_driveE = new Node(10, new DriveWaypointAction(	PathLoader::loadPath("wallToPeg_center.csv", 1.0,
			(CORERobot::getAlliance() == CORERobot::RED)), true, .25, 125.0, true));
	m_dropB = new Node(2, new LoadGearOntoPegAction(), new WaitAction(.25));
	m_driveF = new Node(15, new DriveWaypointAction(AutonPaths::getPegReversePath()));

	addFirstNode(m_driveA);
	m_driveA->addNext(m_dropA);
	m_dropA->addNext(m_driveB);
	m_driveB->addNext(m_turnA);
	m_turnA->addNext(m_driveC);
	m_driveC->addNext(m_driveD);
	m_driveD->addNext(m_turnB);
	m_turnB->addNext(m_driveE);
	m_driveE->addNext(m_dropB);
	m_dropB->addNext(m_driveF);
}
