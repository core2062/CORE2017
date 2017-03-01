#include "Robot.h"
#include "GearOnlyAuton.h"
#include "Actions.h"

using namespace CORE;

GearOnlyAuton::GearOnlyAuton(StartingPosition startingPosition) :
		COREAuton("Gear Only", &m_driveToPeg, true),
		m_driveToPeg(new DriveWaypointAction(getPathFor(startingPosition))),
		m_loadGearOnPeg(new LoadGearOntoPegAction()){

}

void GearOnlyAuton::addNodes() {
m_driveToPeg.addNext(&m_loadGearOnPeg);
}

Path * GearOnlyAuton::getPathFor(StartingPosition startingPosition) {
	return new Path({{{0,0},0}, {{1,1},1}});
}
