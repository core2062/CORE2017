#include "DriveDistanceAction.h"
#include "Robot.h"

DriveDistanceAction::DriveDistanceAction(double speedInFraction, double distanceInInches, bool setHighGear) {
	m_speedInFraction = speedInFraction;
	m_distanceInInches = distanceInInches;
	m_setHighGear = setHighGear;

}
    void DriveDistanceAction::actionInit() {
        //driveMotorFR.CANTalonController->SetEncPosition(0);
        Robot->driveSubsystem.resetEncoders(DriveSide::BOTH);
    	Robot->driveSubsystem.setHighGear(m_setHighGear);
    }
    COREAutonAction::actionStatus DriveDistanceAction::action() {
    	//How far have we gone since the reset?
    	double averDist = Robot->driveSubsystem.getDistanceInInches(DriveSide::BOTH);

    	//Is this less than how far we were supposed to go?
    	if (averDist < m_distanceInInches) {
    		//If yes, set motors to appropriate speed, return CONTINUE.
    		Robot->driveSubsystem.setMotorSpeed(m_speedInFraction, DriveSide::BOTH);
    		return COREAutonAction::CONTINUE;

    	}else{
        	//If no, set motors to zero, return END.
    		Robot->driveSubsystem.setMotorSpeed(0, DriveSide::BOTH);
    		return COREAutonAction::END;

    	}


    	// PLACEHOLDER
    	return COREAutonAction::END;
    }

    void DriveDistanceAction::actionEnd() {
    	Robot->driveSubsystem.setMotorSpeed(0, DriveSide::BOTH);
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
