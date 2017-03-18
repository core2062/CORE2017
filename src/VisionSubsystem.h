#pragma once

#include "CORERobotLib.h"
#include "WPILib.h"

using namespace CORE;

class VisionSubsystem : public CORESubsystem, public CORETask {
public:

    VisionSubsystem();
    void robotInit() override;
    void teleopInit() override;
    void teleop() override;

private:
    const string frontCamera = "front";
    const string gearCamera = "gear";
    string whichCamera = frontCamera;
    shared_ptr<NetworkTable> visionTable;

};
