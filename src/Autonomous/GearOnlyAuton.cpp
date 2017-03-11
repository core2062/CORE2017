#include "Robot.h"
#include "GearOnlyAuton.h"
#include "Actions.h"
#include "AutonPaths.h"

using namespace CORE;

GearOnlyAuton::GearOnlyAuton(StartingPosition startingPosition) :
		COREAuton("Gear Only", 0.0){

}
void GearOnlyAuton::addNodes() {
	m_driveToPeg = new Node(15, new DriveWaypointAction(getForwardPegPath(Robot->getStartingPosition()), true));
	m_loadGearOnPeg = new Node(15, new LoadGearOntoPegAction());
	m_reverseDrive = new Node(15, new DriveWaypointAction(getReversePath(Robot->getStartingPosition())));
	addFirstNode(m_driveToPeg);
	m_driveToPeg->addNext(m_loadGearOnPeg);
	m_loadGearOnPeg->addNext(m_reverseDrive);
}

Path* GearOnlyAuton::getForwardPegPath(StartingPosition startingPosition) {
	switch(startingPosition){
	case StartingPosition::BOILER:
		return PathLoader::loadPath("gearAuton_forward_boiler.csv", 1.0, (CORERobot::getAlliance() == RED));
		break;
	case StartingPosition::FEEDER:
		return PathLoader::loadPath("gearAuton_forward_feeder.csv", 1.0, (CORERobot::getAlliance() == RED));
		break;
	default:
		//AutonPaths::getForwardPegPath();
		return PathLoader::loadPath("gearAuton_forward_center.csv", 1.0, (CORERobot::getAlliance() == RED));
		break;
	}
}

Path* GearOnlyAuton::getReversePath(StartingPosition startingPosition) {
	switch(startingPosition){
	case StartingPosition::BOILER:
		return PathLoader::loadPath("gearAuton_reverse_boiler.csv", 1.0, (CORERobot::getAlliance() == RED));
		break;
	case StartingPosition::FEEDER:
		return PathLoader::loadPath("gearAuton_reverse_feeder.csv", 1.0, (CORERobot::getAlliance() == RED));
		break;
	default:
		//return AutonPaths::getReversePegPath();
		return PathLoader::loadPath("gearAuton_forward_center.csv", 1.0, (CORERobot::getAlliance() == RED));
		break;
	}
}
