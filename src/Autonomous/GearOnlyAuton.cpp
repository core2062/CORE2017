#include "Robot.h"
#include "GearOnlyAuton.h"
#include "Actions.h"

using namespace CORE;

GearOnlyAuton::GearOnlyAuton(StartingPosition startingPosition) :
		COREAuton("Gear Only", &m_driveToPeg, true),
		m_driveToPeg(nullptr),
		m_loadGearOnPeg(new LoadGearOntoPegAction()),
		m_reverseDrive(nullptr){

}

void GearOnlyAuton::addNodes() {
m_driveToPeg.addAction(new DriveWaypointAction(getForwardPath(Robot->getStartingPosition()), true));
m_driveToPeg.addNext(&m_loadGearOnPeg);
m_reverseDrive.addAction(new DriveWaypointAction(getReversePath(Robot->getStartingPosition())));
m_loadGearOnPeg.addNext(&m_reverseDrive);
}

Path * GearOnlyAuton::getPathFor(StartingPosition startingPosition) {
	return new Path({{{162,0},25}, {{162,90},25}});
}

Path* GearOnlyAuton::getForwardPath(StartingPosition startingPosition) {
	switch(startingPosition){
	case StartingPosition::BOILER:
		return PathLoader::loadPath("gearAuton_forward_boiler.csv", -1.0, (CORERobot::getAlliance() == RED));
		break;
	case StartingPosition::FEEDER:
		return PathLoader::loadPath("gearAuton_forward_feeder.csv", -1.0, (CORERobot::getAlliance() == RED));
		break;
	default:
		return PathLoader::loadPath("gearAuton_forward_center.csv", -1.0, (CORERobot::getAlliance() == RED));
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
		return PathLoader::loadPath("gearAuton_reverse_center.csv", 1.0, (CORERobot::getAlliance() == RED));
		break;
	}
}
