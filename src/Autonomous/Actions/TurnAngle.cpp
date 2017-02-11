#include "AHRS.h"
#include <Autonomous/Actions/TurnAngle.h>
#include "Robot.h"

TurnAngle::TurnAngle(double angle, double tolerance): m_angle(angle), m_tolerance(tolerance) {


}

void TurnAngle::actionInit() {
	Robot::driveSubsystem->startTurning(m_angle, m_tolerance);
}

actionStatus TurnAngle::action() {
	//If we are still turning, CONTINUEs
	if (Robot::driveSubsystem-> isTurning()){
		return actionStatus::CONTINUE;
	}
	//If we are no longer turning, END
	return actionStatus::END;
}

void TurnAngle::actionEnd() {

}
