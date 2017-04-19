#include "GearBoilerAuton.h"
#include "Actions.h"
#include "Robot.h"
#include "AutonPaths.h"

GearBoilerAuton::GearBoilerAuton() :
		COREAuton("Gear and Boiler Auton", 0.0){}

void GearBoilerAuton::addNodes() {
	m_setLowGear = new Node(10, new DriveShiftAction(GearPosition::LOW_GEAR));
	if( Robot->getStartingPosition() == StartingPosition::BOILER){
		m_driveForward = new Node( 3, new DriveDistanceAction(-1.0, Robot->gearAuton.boilerForwardDist.Get()));
		m_turnToPeg = new Node( 3, new TurnAngleAction(Rotation2d::fromDegrees(60 * Robot->getAlliance()), 5));
	}
	m_driveToPeg = new Node(6.5, new VisionAlignGearAction());
	m_loadGearOnPeg = new Node(15, new LoadGearOntoPegAction(), new WaitAction(.5));
	m_driveToBoiler = new Node(10, new DriveWaypointAction(AutonPaths::getPegToBoilerPath(), false));
	m_dumpBallsInBoiler = new Node(5, new DumpBallsAction(1.5));
	m_cross = new Node(9, new DriveWaypointAction(AutonPaths::getCrossFieldPath(), true, .25, 125, false));
	m_goHigh = new Node(2,  new DriveShiftAction(GearPosition::HIGH_GEAR));
	m_driveCross = new Node(5, new DriveDistanceAction(-1.0, 150, true));

	addFirstNode(m_setLowGear);
	if(m_driveForward != nullptr){
		m_setLowGear->addNext(m_driveForward);
		m_driveForward->addNext(m_turnToPeg);
		m_turnToPeg->addNext(m_driveToPeg);
	} else {
		m_setLowGear->addNext(m_driveToPeg);
	}
	m_driveToPeg->addNext(m_loadGearOnPeg);
	m_loadGearOnPeg->addNext(m_driveToBoiler);
	m_driveToBoiler->addNext(m_dumpBallsInBoiler);

	if (SmartDashboard::GetBoolean("Auto Cross Field", false)){
		m_dumpBallsInBoiler->addNext(m_goHigh);
		m_goHigh->addNext(m_cross);
		m_cross->addNext(m_driveCross);
	}
}

