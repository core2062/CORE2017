#include "DriveForwardAuton.h"
#include "Robot.h"
#include "Constants.h"
#include "AutonPaths.h"

using namespace CORE;

DriveForwardAuton::DriveForwardAuton(double speedInFraction, double distanceInFeet) :
	COREAuton("Drive Forward", 0.0)
{}

void DriveForwardAuton::addNodes() {
	m_setLowGearPosition = new Node(10, new DriveShiftAction(GearPosition::LOW_GEAR));
	m_moveForwardToLine = new Node(5, new DriveWaypointAction(AutonPaths::getDriveForwardPath(), true));
	m_spinInCircles = new Node(10, new GearFlapAction(ActuationType::OPEN));
	addFirstNode(m_setLowGearPosition);
	m_setLowGearPosition->addNext(m_moveForwardToLine);
	m_moveForwardToLine->addNext(m_spinInCircles);
}
