#include "TurnAngleAction.h"
#include <Robot.h>

TurnAngleAuton::TurnAngleAuton(double angle, double tolerance): m_angle(angle), m_tolerance(tolerance) {


}

void TurnAngleAuton::actionInit() {
    Robot::driveSubsystem->startTurning(m_angle, m_tolerance);
}

COREAutonAction::actionStatus TurnAngleAuton::action() {
    //If we are still turning, CONTINUEs
    if (Robot::driveSubsystem-> isTurning()){
        return COREAutonAction::CONTINUE;
    }
    //If we are no longer turning, END
    return COREAutonAction::END;
}

void TurnAngleAuton::actionEnd() {

}
