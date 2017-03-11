#include "DriveWaypointController.h"
#include "Robot.h"

DriveWaypointController::DriveWaypointController():
	m_path(),
    m_tracker(TankTracker::GetInstance()),
	m_pursuit(0,0,.1,m_path,false,0)
{
    TankTracker::GetInstance()->init(Robot->driveSubsystem.getLeftMaster(), Robot->driveSubsystem.getRightMaster(), Robot->driveSubsystem.getGyro()),
    std::cout << "Waypoint Controller Init" << std::endl;
}

void DriveWaypointController::preLoopTask() {
	m_tracker->loop();
	Position2d current = m_tracker->getLatestFieldToVehicle();
	SmartDashboard::PutNumber("Robot X" , current.getTranslation().getX());
	SmartDashboard::PutNumber("Robot Y" , current.getTranslation().getY());
}

void DriveWaypointController::postLoopTask() {
	if ( m_enabled && (Robot->getMode() == CORE::gameMode::AUTON)){
		enabledLoop();
	}
}

void DriveWaypointController::enabledLoop(){
	updatePathFollower();
}

void DriveWaypointController::enable() {
	m_enabled = true;
}

void DriveWaypointController::disable() {
	m_enabled = false;
}

void DriveWaypointController::init() {
	m_tracker->reset(Timer::GetFPGATimestamp(), Position2d());
}

void DriveWaypointController::startPath(Path path, bool reversed,
		double maxAccel, double tolerance) {
	m_pursuit = AdaptivePursuit(24.0, maxAccel, .025, path, reversed, tolerance);
}

void DriveWaypointController::resetTracker(Position2d initialPos) {
	m_tracker->reset(Timer::GetFPGATimestamp(), initialPos);
}

bool DriveWaypointController::isDone() {
	return m_pursuit.isDone();
}

bool DriveWaypointController::checkEvent(std::string event) {
	return m_pursuit.checkEvent(event);
}

void DriveWaypointController::updatePathFollower() {
	Position2d pos = m_tracker->getLatestFieldToVehicle();
	Position2d::Delta command = m_pursuit.update(pos, Timer::GetFPGATimestamp());
//	std::cout << command.dx << "   " << command.dy << "   " << command.dtheta << std::endl;
	VelocityPair setpoint = TankKinematics::inverseKinematics(command);
	double maxVel = 0.0;
	maxVel = max(maxVel, setpoint.left);
	maxVel = max(maxVel, setpoint.right);
	if (maxVel > 100){
		double scaling = 100 / maxVel;
		setpoint = VelocityPair(setpoint.left * scaling, setpoint.right * scaling);
	}
	Robot->driveSubsystem.setMotorSpeed(setpoint.left * .01, setpoint.right * .01);
}
