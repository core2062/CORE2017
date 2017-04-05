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

private:
    const string frontCamera = "front";
    const string gearCamera = "gear";
    string whichCamera = frontCamera;
    shared_ptr<NetworkTable> visionTable;
    std::vector<double> m_timeOffsets;
    double m_timeOffset = 0.0;
    RobotFrame m_visionFrame;
    Path m_pathToPeg;

};
