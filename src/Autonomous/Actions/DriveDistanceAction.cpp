#include "Robot.h"
#include <Autonomous/Actions/DriveDistance.h>

DriveDistance::DriveDistance(double speedInFraction, double distanceInFeet) {
	m_speedInFraction = speedInFraction;
	m_distanceInFeet = distanceInFeet;
}

    void DriveDistance::actionInit() {
        //driveMotorFR.CANTalonController->SetEncPosition(0);
        Robot::driveSubsystem->resetEncoders(DriveSide::BOTH);
    }
    actionStatus DriveDistance::action() {
    	//How far have we gone since the reset?
    	double averDist = Robot::driveSubsystem->getDistanceInFeet(DriveSide::BOTH);

    	//Is this less than how far we were supposed to go?
    	if (averDist < m_distanceInFeet) {
    		//If yes, set motors to appropriate speed, return CONTINUE.
    		Robot::driveSubsystem->setMotorSpeed(m_speedInFraction, DriveSide::BOTH);
    		return actionStatus::CONTINUE;

    	}else{
        	//If no, set motors to zero, return END.
    		Robot::driveSubsystem->setMotorSpeed(0, DriveSide::BOTH);
    		return actionStatus::END;

    	}
    	// PLACEHOLDER
    	return actionStatus::END;
    }

    void DriveDistance::actionEnd() {
    	Robot::driveSubsystem->setMotorSpeed(0, DriveSide::BOTH);
    }


//        if(abs(driveMotorFR.CANTalonController->GetEncPosition()) < 10000) {
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
