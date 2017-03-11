#include "DriveForwardAuton.h"
#include "Robot.h"
#include "Constants.h"
#include "AutonPaths.h"

using namespace CORE;

DriveForwardAuton::DriveForwardAuton(double speedInFraction, double distanceInFeet) :
	COREAuton("Drive Forward", 0.0) //,
//	m_moveForwardToLine(new DriveWaypointAction(new Path({{{0,162},-100}, {{-12,162},-100}, {{-36,162},-100}/*, {{37,162},25}*/}),true)),
//	m_moveForwardToLine(new DriveWaypointAction(PathLoader::loadPath("driveForward.csv", -1.0), true)),
//	m_moveForwardToLine(new DriveWaypointAction(PathLoader::loadPath("gearAuton_forward_boiler.csv", -1.0), true)),
//	m_spinInCircles(new GearFlapAction(ActuationType::OPEN))
{

}

void DriveForwardAuton::addNodes() {
	m_moveForwardToLine = new Node(5, new DriveWaypointAction(PathLoader::loadPath("driveForward.csv", 1.0, true)));
	m_spinInCircles = new Node(10, new GearFlapAction(ActuationType::OPEN));
	addFirstNode(m_moveForwardToLine);
	m_moveForwardToLine->addNext(m_spinInCircles);
}
