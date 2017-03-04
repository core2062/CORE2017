#include "DriveForwardAuton.h"
#include "Robot.h"
#include "Constants.h"

using namespace CORE;

DriveForwardAuton::DriveForwardAuton(double speedInFraction, double distanceInFeet) :
	COREAuton("Drive Forward", &m_moveForwardToLine, true) ,
	m_moveForwardToLine(new DriveWaypointAction(new Path({{{0,0},25}, {{1,1},25}}))),
	m_spinInCircles(new DriveWaypointAction(new Path({{{0,0},0}, {{1,1},25}})), new GearFlapAction(ActuationType::OPEN)) {

}

void DriveForwardAuton::addNodes() {
	m_moveForwardToLine.addNext(&m_spinInCircles);
}
