#include "DriveForwardAuton.h"
#include "Robot.h"

using namespace CORE;

DriveForwardAuton::DriveForwardAuton(double speedInFraction, double distanceInFeet) :
	COREAuton("Drive Forward", &m_moveForwardToLine, true) ,
	m_moveForwardToLine(new DriveWaypointAction(Path({{{0,0},0}, {{1,1},1}}))),
	m_spinInCircles(new DriveWaypointAction(Path({{{0,0},0}, {{1,1},1}})), new GearFlapAction(OPEN)) {

}

void DriveForwardAuton::addNodes() {
	m_moveForwardToLine.addNext(&m_spinInCircles);
}
