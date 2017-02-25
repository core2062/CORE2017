#include "TurnAngleAction.h"
#include "Robot.h"

TurnAngleAction::TurnAngleAction(double angle, double tolerance, bool setHighGear): m_angle(angle), m_tolerance(tolerance), m_setHighGear() {

}

void TurnAngleAction::actionInit() {
	Robot->driveSubsystem.startTurning(m_angle, m_tolerance);
	Robot->driveSubsystem.setHighGear(m_setHighGear);
}

COREAutonAction::actionStatus TurnAngleAction::action() {
    //If we are still turning, CONTINUE
    if (Robot->driveSubsystem.isTurning()){
        return COREAutonAction::CONTINUE;
    }
    //If we are no longer turning, END
    return COREAutonAction::END;
}

void TurnAngleAction::actionEnd() {
}
