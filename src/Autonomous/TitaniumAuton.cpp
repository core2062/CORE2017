#include "Robot.h"
#include "Actions.h"
#include "AutonPaths.h"
#include "TitaniumAuton.h"

using namespace CORE;

TitaniumAuton::TitaniumAuton(StartingPosition startingPosition) :
	COREAuton("Titanium Auton", 0.0){

}

void TitaniumAuton::addNodes() {
	m_setLowGear = new Node (1, new DriveShiftAction(GearPosition::LOW_GEAR));
	m_driveToHopper = new Node(4.5, new DriveWaypointAction(AutonPaths::getWallToFarHopperPath(),true));
	m_lowerLift = new Node(4.5, new SetLiftPositionAction(false, true));
	m_driveToBoiler = new Node(4.5, new DriveWaypointAction(AutonPaths::getFarHopperToBoilerPath(),true));
	m_dumpBalls = new Node(4.5, new DumpBallsAction(3.5));

	addFirstNode(m_setLowGear);
	m_setLowGear->addNext(m_driveToHopper);
	m_driveToHopper->addNext(m_lowerLift);
	m_lowerLift->addNext(m_driveToBoiler);
	m_driveToBoiler->addNext(m_dumpBalls);
}
