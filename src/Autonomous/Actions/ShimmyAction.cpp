#include "ShimmyAction.h"
#include "Math.h"
#include "Robot.h"

ShimmyAction::ShimmyAction(double numberOfSeconds, double severityOfShimmy):m_shimmyTimer(){
	m_numberOfSeconds = numberOfSeconds;
	m_severityOfShimmy = severityOfShimmy;
}

void ShimmyAction::actionInit() {
	m_shimmyTimer.Reset();
	m_shimmyTimer.Start();
}

COREAutonAction::actionStatus ShimmyAction::action() {
	double elapsed = m_shimmyTimer.Get();

	//Find if elapsed is greater than number of seconds
	//If it is, end action

	if (elapsed >= m_numberOfSeconds){
		return COREAutonAction::actionStatus::END;
	}
	double fraction = (elapsed % m_numberOfSeconds);

	//If fraction is less than half
	//Shimmy left
	if (fraction < 0.5){
		Robot->driveSubsystem.setMotorSpeed(-m_severityOfShimmy, m_severityOfShimmy);
	}

	//Otherwise fraction is greater than or equal to half
	//Shimmy right
	if (fraction >= 0.5){
		Robot->driveSubsystem.setMotorSpeed(m_severityOfShimmy, -m_severityOfShimmy);
	}
	return COREAutonAction::actionStatus::CONTINUE;
}

void ShimmyAction::actionEnd() {
	Robot->driveSubsystem.setMotorSpeed(0.0, 0.0);
}


