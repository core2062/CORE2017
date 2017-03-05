#pragma once

#include "CORERobotLib.h"
#include "WPILib.h"

using namespace CORE;

class HopperSubsystem : public CORESubsystem {
public:
    HopperSubsystem();
    void robotInit() override;
    void teleopInit() override;
    void teleop() override;
    void setLiftTop();
    void setLiftBottom();
    void setLift(double val);
    void openFlap();
    void closeFlap();
    bool hopperIsUp();
    bool hopperIsDown();
    void turnOnIntake();
    void turnOffIntake();
    void setIntake(double val);
    bool intakeIsOn();
    double getLiftSpeed();
    double getLiftEncoder();
    bool flapIsOpen();


private:
    COREMotor m_liftMotor, m_intakeMotor;
    //COREMotionProfile* m_liftController;
    Servo m_leftDumpFlapServo, m_rightDumpFlapServo;
    COREConstant<double> m_liftBottomPos, m_liftTopPos, m_liftRaiseVel, m_liftLowerVel, m_liftTolerance, m_flapTopPos, m_flapBottomPos, m_intakeSpeed,
			m_liftPID_P, m_liftPID_I, m_liftPID_D, m_liftPID_Pa, m_liftPID_Ia, m_liftPID_Da;
//    COREPID m_liftPID;

//    DigitalInput m_bottomLimit;
//    DigitalInput m_topLimit;

    bool m_flapIsOpen;

    struct PID{
    	int setPoint = 0.0;

    	double PPos = 0.0;
    	double IPos = 0.0;
    	double DPos = 0.0;

    	double PNeg = 0.0;
    	double INeg = 0.0;
    	double DNeg = 0.0;

    	double error = 0.0;
    	double lastError = 0.0;
    	double totalError = 0.0;
    	Timer integralTimer;
    	double deltaTime = 0.0;
    	double lastTime = 0.0;

    	void start(int setpoint = 0){
    		if(setpoint != setPoint){
    			integralTimer.Reset();
    			integralTimer.Start();
    			error = 0.0;
    			lastError = 0.0;
    			totalError = 0.0;
    			deltaTime = 0;
    			lastTime = Timer::GetFPGATimestamp();
    			setPoint = setpoint;
    		}
    	}

    	void updateTime(){
    		double currentTime = Timer::GetFPGATimestamp();
    		deltaTime = currentTime - lastTime;
    		lastTime = currentTime;
    	}

    	double integral(){
    		double totalTime = integralTimer.Get();
    		return totalError / totalTime;
    	}

    	double derivative(){
    		double rise = error - lastError;
    		double slope = rise / deltaTime;
    		return slope;
    	}

    	double calculate(int position){
    		error = position - setPoint;
    		totalError += error;

    		double p, i, d;
    		if(error <= 0){
    			p = error * PPos;
    			i = integral() * IPos;
    			d = derivative() * DPos;
    		} else {
    			p = error * PNeg;
    			i = integral() * INeg;
    			d = derivative() * DNeg;

    		}
    		lastError = error;
    		return (p + i - d);
    	}
    };

    PID m_liftPID;
};

class IntakeController : public CORETask {
public:
	IntakeController();
	void postLoopTask() override;
	void disabledTask() override;
};
