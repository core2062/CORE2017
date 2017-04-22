#pragma once
#include "CORERobotLib.h"
#include "WPILib.h"
#include "WaypointFollower/RobotFrame.h"

using namespace CORE;

class VisionSubsystem : public CORESubsystem, public CORETask {
public:

    VisionSubsystem();
    void robotInit() override;
    void teleopInit() override;
    void teleop() override;
    void autonInitTask() override;
    void preLoopTask() override;
    Rotation2d getError();
    double getErrorPercent();
    Path * getPath();
    RobotFrame * getFrame();
    void calculatePath();
    double getGearX();

    double getUltraDist();

    COREConstant<double> gearPlaceDist;
    COREConstant<double> ultrakP;
    shared_ptr<NetworkTable> visionTable;
private:
    const string frontCamera = "front";
    const string gearCamera = "gear";
    string whichCamera = frontCamera;
    std::vector<double> m_timeOffsets;
    double m_timeOffset = 0.0;
    double m_lastPiTime = 0.0;
    double m_pegX = 0.0;

    Rotation2d m_targetRotation;

    COREConstant<double> m_imageWidth;
    COREConstant<double> m_horizontalFieldOfView;
    COREConstant<double> m_pegApproachDist;
    COREConstant<int> m_pegApproachSamples;

    RobotFrame m_visionFrame;
    Path m_pathToPeg;

    AnalogInput m_leftUltra;
    AnalogInput m_rightUltra;
    AnalogInput m_jumper;
};
