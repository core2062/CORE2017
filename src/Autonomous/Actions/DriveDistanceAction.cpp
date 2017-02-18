#include "DriveDistanceAction.h"
#include "Robot.h"

DriveDistanceAction::DriveDistanceAction(double speedInFraction, double distanceInFeet) {
	m_speedInFraction = speedInFraction;
	m_distanceInFeet = distanceInFeet;
}

    void DriveDistanceAction::actionInit() {
        //driveMotorFR.m_CANTalonController->SetEncPosition(0);
        Robot::driveSubsystem->resetEncoders(DriveSide::BOTH);
    }
    COREAutonAction::actionStatus DriveDistanceAction::action() {
    	//How far have we gone since the reset?
    	double averDist = Robot::driveSubsystem->getDistanceInFeet(DriveSide::BOTH);

    	//Is this less than how far we were supposed to go?
    	if (averDist < m_distanceInFeet) {
    		//If yes, set motors to appropriate speed, return CONTINUE.
    		Robot::driveSubsystem->setMotorSpeed(m_speedInFraction, DriveSide::BOTH);
    		return COREAutonAction::CONTINUE;

    	}else{
        	//If no, set motors to zero, return END.
    		Robot::driveSubsystem->setMotorSpeed(0, DriveSide::BOTH);
    		return COREAutonAction::END;

    	}
    	// PLACEHOLDER
    	return actionStatus::END;
    }

    void DriveDistanceAction::actionEnd() {
    	Robot::driveSubsystem->setMotorSpeed(0, DriveSide::BOTH);
    }


//        if(abs(driveMotorFR.m_CANTalonController->GetEncPosition()) < 10000) {
//        	Robot::CORERobot::CORESubsystem
//            return actionStatus::CONTINUE;
//        } else {
//        	//driveMotorFR.Set(0);
//        	//driveMotorFL.Set(0);
//        	//driveMotorBR.Set(0);
//        	//driveMotorBL.Set(0);
//            return actionStatus::END;
//        }
//    }
