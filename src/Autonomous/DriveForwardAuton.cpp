#include "DriveForwardAuton.h"
#include "Robot.h"
#include "Constants.h"

using namespace CORE;

DriveForwardAuton::DriveForwardAuton(double speedInFraction, double distanceInFeet) :
	COREAuton("Drive Forward", &m_moveForwardToLine, true) ,
//	m_moveForwardToLine(new DriveWaypointAction(new Path({{{0,162},-100}, {{-12,162},-100}, {{-36,162},-100}/*, {{37,162},25}*/}),true)),
	m_moveForwardToLine(new DriveWaypointAction(PathLoader::loadPath("driveForward.csv", -1.0), true)),
	m_spinInCircles(new GearFlapAction(ActuationType::OPEN)) {

}

void DriveForwardAuton::addNodes() {
	m_moveForwardToLine.addNext(&m_spinInCircles);
}
