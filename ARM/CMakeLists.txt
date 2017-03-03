set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_SYSTEM_NAME Linux)

if(WIN32)
    set(WPILIB_HOME C:/Users/Andrew/wpilib/cpp/current)
    #TODO: This needs to be changed to work for everyone
else()
    set(WPILIB_HOME $ENV{HOME}/wpilib/cpp/current)
endif()

set(PROJECT_NAME "ARM_${PROJECT_NAME}")

set(CORERobotLib ${PROJECT_SOURCE_DIR}/CORERobotLib)

if(WIN32)
    set(CMAKE_C_COMPILER C:/frc/bin/arm-frc-linux-gnueabi-gcc)
    set(CMAKE_CXX_COMPILER C:/frc/bin/arm-frc-linux-gnueabi-g++)
else()
    set(CMAKE_C_COMPILER /usr/bin/arm-frc-linux-gnueabi-gcc)
    set(CMAKE_CXX_COMPILER /usr/bin/arm-frc-linux-gnueabi-g++)
endif()

include_directories(${CORERobotLib}/3rdparty/CTRE/include)
link_directories(${CORERobotLib}/3rdparty/CTRE/Linux/arm)
include_directories(${CORERobotLib}/3rdparty/navx-mxp/include)
link_directories(${CORERobotLib}/3rdparty/navx-mxp/Linux/arm)

include_directories(${WPILIB_HOME}/include)
link_directories(${WPILIB_HOME}/lib)

include_directories(${CORERobotLib})
include_directories(${CORERobotLib}/src)

# For quick list run
# find src -iname "*.cpp"
# in project root
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
        ${CORERobotLib}/src/WaypointFollower/Translation2d.cpp)

include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} libwpi.so libnavx_frc_cpp.a libCTRLib.a)