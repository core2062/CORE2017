#include "TurnAngleAction.h"
#include <Robot.h>

TurnAngleAction::TurnAngleAction(double angle, double tolerance): m_angle(angle), m_tolerance(tolerance) {


}

void TurnAngleAction::actionInit() {
	Robot->driveSubsystem.startTurning(m_angle, m_tolerance);
}

COREAutonAction::actionStatus TurnAngleAction::action() {
    //If we are still turning, CONTINUEs
    if (Robot->driveSubsystem.isTurning()){
        return COREAutonAction::CONTINUE;
    }
    //If we are no longer turning, END
    return COREAutonAction::END;
}

void TurnAngleAction::actionEnd() {

}
