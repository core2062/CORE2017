#include "2GearAuton.h"
#include "Actions.h"
#include "Robot.h"
#include "AutonPaths.h"

TwoGearAuton::TwoGearAuton() :
	COREAuton("Two Gear Auton", 0.0){}

void TwoGearAuton::addNodes() {
	m_driveToPeg = new Node(7, new DriveWaypointAction(AutonPaths::getWallToPegPath(), true, .25, 125.0, true), new DriveShiftAction(GearPosition::LOW_GEAR));
	m_dropA = new Node(2, new LoadGearOntoPegAction(), new WaitAction(.25));
	m_driveToTurn = new Node(10, new DriveWaypointAction(	PathLoader::loadPath("2gearA.csv", 1.0,
			(CORERobot::getAlliance() == CORERobot::RED)), false, .25, 250.0, false));
	m_turnToPickup = new Node(3, new TurnAngleAction(Rotation2d::fromDegrees(-135 * CORERobot::getAlliance()), 15));
	m_driveToPickup = new Node(10, new DriveWaypointAction(	PathLoader::loadPath("2gearB.csv", 1.0,
			(CORERobot::getAlliance() == CORERobot::RED)), true, .25, 250.0, false), new PickupGearAction());
	m_driveTowardsCenter = new Node(10, new DriveWaypointAction(	PathLoader::loadPath("2gearC.csv", 1.0,
			(CORERobot::getAlliance() == CORERobot::RED)), false, 25, 250.0, false), new PickupGearAction(true));
	m_turnToPeg = new Node(3, new TurnAngleAction(Rotation2d::fromDegrees(0), 10));

	m_driveBackToPeg = new Node(5, new DriveWaypointAction(AutonPaths::getWallToPegPath(), true, .25, 125.0, true));

	m_waitForVision = new Node(10, new WaitAction(.25));
	m_driveOnPeg = new Node(7, new VisionPathAction());

	m_dropB = new Node(2, new LoadGearOntoPegAction(), new WaitAction(.25));

	m_driveReverse = new Node(15, new DriveWaypointAction(AutonPaths::getPegReversePath()));

	m_driveToBoiler = new Node(10, new DriveWaypointAction(AutonPaths::getPegToBoilerPath(), false, .25, 250, true));
	m_dumpBallsInBoiler = new Node(5, new DumpBallsAction(1.5));

	m_prepCrossA = new Node(12, new DriveWaypointAction(AutonPaths::getPegToCrossPathA(), false, .25, 150.0, false));
	m_prepCrossB = new Node(12, new DriveWaypointAction(AutonPaths::getPegToCrossPathB(), true, .25, 1500.0, false));
	m_cross = new Node(6, new DriveDistanceAction(-1.0, 100, false));

	addFirstNode(m_driveToPeg);
	m_driveToPeg->addNext(m_dropA);
	m_dropA->addNext(m_driveToTurn);
	m_driveToTurn->addNext(m_turnToPickup);
	m_turnToPickup->addNext(m_driveToPickup);
	m_driveToPickup->addNext(m_driveTowardsCenter);
	m_driveTowardsCenter->addNext(m_turnToPeg);

	if (SmartDashboard::GetBoolean("Use Vision", false)){
		m_turnToPeg->addNext(m_waitForVision);
		m_waitForVision->addNext(m_driveOnPeg);
		m_driveOnPeg->addNext(m_dropB);
	} else {
		m_turnToPeg->addNext(m_driveBackToPeg);
		m_driveBackToPeg->addNext(m_dropB);
	}

	if(SmartDashboard::GetBoolean("Two Gear Boiler", false)){
		m_dropB->addNext(m_driveToBoiler);
		m_driveToBoiler->addNext(m_dumpBallsInBoiler);
	} else if (SmartDashboard::GetBoolean("Auto Cross Field", false)){
		m_dropB->addNext(m_prepCrossA);
		m_prepCrossA->addNext(m_prepCrossB);
		m_prepCrossB->addNext(m_cross);
	} else {
		m_dropB->addNext(m_driveReverse);
	}
}
