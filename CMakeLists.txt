cmake_minimum_required(VERSION 2.8)

project(CORE2017)

# Team number
set(TEAM_NUMBER 2062)

# Robot target
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g")

add_subdirectory(ARM)

set(WPILIB_HOME $ENV{HOME}/wpilib/cpp/current)
set(${PROJECT_NAME} ARM_${PROJECT_NAME})

set(CORERobotLib ${PROJECT_SOURCE_DIR}/CORERobotLib)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

#include_directories(${PROJECT_SOURCE_DIR}/3rdparty/CANTalon/include)
#include_directories(${PROJECT_SOURCE_DIR}/3rdparty/NavX/include)

#include_directories(${CORERobotLib}/3rdparty/CTRE/include)
#link_directories(${CORERobotLib}/3rdparty/CTRE/Linux/arm)
#include_directories(${CORERobotLib}/3rdparty/navx-mxp/include)
#link_directories(${CORERobotLib}/3rdparty/navx-mxp/Linux/arm)

include_directories(${CORERobotLib}/src/Fake_WPILib)

include_directories(${CORERobotLib})
include_directories(${CORERobotLib}/src)


# For quick list run
# find src -iname "*.cpp"
# in project root
#set(SOURCE_FILES src/Robot.cpp)
set(SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/Robot.cpp
        ${PROJECT_SOURCE_DIR}/src/DriveSubsystem.cpp
        ${PROJECT_SOURCE_DIR}/src/HopperSubsystem.cpp
        ${PROJECT_SOURCE_DIR}/src/GearSubsystem.cpp
        ${PROJECT_SOURCE_DIR}/src/ClimberSubsystem.cpp
        ${PROJECT_SOURCE_DIR}/src/Controllers/DriveGyroController.cpp
        ${PROJECT_SOURCE_DIR}/src/Controllers/DriveOpenController.cpp
        ${PROJECT_SOURCE_DIR}/src/Controllers/DriveWaypointController.cpp

        #        ${PROJECT_SOURCE_DIR}/src/Autonomous/Actions/DriveDistanceAction.cpp
        #        ${PROJECT_SOURCE_DIR}/src/Autonomous/Actions/DumpBallsAction.cpp
        #        ${PROJECT_SOURCE_DIR}/src/Autonomous/Actions/IntakeBallsAction.cpp
        #        ${PROJECT_SOURCE_DIR}/src/Autonomous/Actions/LoadGearOntoPegAction.cpp
        #        ${PROJECT_SOURCE_DIR}/src/Autonomous/Actions/TurnAngleAction.cpp
        #        ${PROJECT_SOURCE_DIR}/src/Autonomous/Actions/VisionGetBallsAction.cpp
        #        ${PROJECT_SOURCE_DIR}/src/Autonomous/Actions/VisionAlignGearAction.cpp

        ${CORERobotLib}/src/COREAuton.cpp
        ${CORERobotLib}/src/COREConstant.cpp
        ${CORERobotLib}/src/COREDataLog.cpp
        ${CORERobotLib}/src/COREDrive/COREEtherDrive.cpp
        ${CORERobotLib}/src/COREDrive/CORESwerveDrive.cpp
        ${CORERobotLib}/src/COREDrive.cpp
        ${CORERobotLib}/src/COREHardware/COREEncoder.cpp
        ${CORERobotLib}/src/COREHardware/COREJoystick.cpp
        ${CORERobotLib}/src/COREHardware/COREMotor.cpp
        ${CORERobotLib}/src/COREHardware/CORESensor.cpp
        ${CORERobotLib}/src/COREHardware/CORETimer.cpp
        ${CORERobotLib}/src/COREHardware.cpp
        ${CORERobotLib}/src/CORELog.cpp
        ${CORERobotLib}/src/COREPID.cpp
        ${CORERobotLib}/src/CORERobot.cpp
        ${CORERobotLib}/src/COREScheduler.cpp
        ${CORERobotLib}/src/COREController/COREMotionProfile.cpp
        ${CORERobotLib}/src/COREController.cpp
        ${CORERobotLib}/src/CORETask.cpp
        ${CORERobotLib}/src/WaypointFollower/AdaptivePursuit.cpp
        ${CORERobotLib}/src/WaypointFollower/InterpolatingMap.cpp
        ${CORERobotLib}/src/WaypointFollower/Path.cpp
        ${CORERobotLib}/src/WaypointFollower/PathSegment.cpp
        ${CORERobotLib}/src/WaypointFollower/Position2d.cpp
        ${CORERobotLib}/src/WaypointFollower/Rotation2d.cpp
        ${CORERobotLib}/src/WaypointFollower/TankKinematics.cpp
        ${CORERobotLib}/src/WaypointFollower/TankTracker.cpp
        ${CORERobotLib}/src/WaypointFollower/Translation2d.cpp
        ${CORERobotLib}/src/Fake_WPILib/WPILib.cpp
        ${CORERobotLib}/src/Fake_WPILib/CANTalon.cpp)

# Deploy target

include_directories(src)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME})


#add_frc_deploy(deploy ${TEAM_NUMBER} $<TARGET_FILE:${PROJECT_NAME}>)
