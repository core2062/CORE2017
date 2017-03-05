#include "Robot.h"
#include "GearOnlyAuton.h"
#include "Actions.h"

using namespace CORE;

GearOnlyAuton::GearOnlyAuton(StartingPosition startingPosition) :
		COREAuton("Gear Only", &m_driveToPeg, true),
		m_driveToPeg(new DriveWaypointAction(getPathFor(startingPosition))),
		m_loadGearOnPeg(new LoadGearOntoPegAction()),
		m_reverseDrive(new DriveWaypointAction(new Path({{{162, 90}, 25}, {{162,60}, 25}}))){

}

void GearOnlyAuton::addNodes() {
m_driveToPeg.addNext(&m_loadGearOnPeg);
m_loadGearOnPeg.addNext(&m_reverseDrive);
}

Path * GearOnlyAuton::getPathFor(StartingPosition startingPosition) {
	return new Path({{{162,0},25}, {{162,90},25}});
}
