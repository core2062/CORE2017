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
    void preLoopTask() override;
    Path * getPath();
    RobotFrame * getFrame();
    void calculatePath();

private:
    const string frontCamera = "front";
    const string gearCamera = "gear";
    string whichCamera = frontCamera;
    shared_ptr<NetworkTable> visionTable;
    std::vector<double> m_timeOffsets;
    double m_timeOffset = 0.0;

    COREConstant<double> m_imageWidth;
    COREConstant<double> m_imageHeight;
    COREConstant<double> m_cameraPegDeltaH;
    COREConstant<double> m_verticalFieldOfView;
    COREConstant<double> m_horizontalFieldOfView;
    COREConstant<double> m_pegPlaceDist;
    COREConstant<double> m_pegApproachDist;
    COREConstant<int> m_pegApproachSamples;

    RobotFrame m_visionFrame;
    Path m_pathToPeg;

};
