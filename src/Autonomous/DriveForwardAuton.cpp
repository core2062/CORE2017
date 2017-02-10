#include "DriveForwardAuton.h"
#include "Robot.h"


DriveForwardAuton() : COREAuton("Drive Forward", &m_driveForward, true) , m_driveForward(new driveDistance()) {

}

void DriveForwardAuton::addNodes() {

}
