cmake_minimum_required(VERSION 3.6)

project(CORE2017)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(CORERobotLib)

include_directories(src)

set(SOURCE_FILES
        src/Autonomous/2GearAuton.cpp
        src/Autonomous/Actions/DriveDistanceAction.cpp
        src/Autonomous/Actions/DriveForwardWithoutPathAction.cpp
        src/Autonomous/Actions/DriveWaypointAction.cpp
        src/Autonomous/Actions/DumpBallsAction.cpp
        src/Autonomous/Actions/GearFlapAction.cpp
        src/Autonomous/Actions/HopperFlapAction.cpp
        src/Autonomous/Actions/LoadGearOntoPegAction.cpp
        src/Autonomous/Actions/PickupGearAction.cpp
        src/Autonomous/Actions/SetLiftPositionAction.cpp
        src/Autonomous/Actions/TurnAngleAction.cpp
        src/Autonomous/Actions/VisionPathAction.cpp
        src/Autonomous/AutonPaths.cpp
        src/Autonomous/DriveForwardAuton.cpp
        src/Autonomous/GearBoilerAuton.cpp
        src/Autonomous/GearHopperBoilerAuton.cpp
        src/Autonomous/GearOnlyAuton.cpp
        src/ClimberSubsystem.cpp
        src/Controllers/DriveGyroController.cpp
        src/Controllers/DriveOpenController.cpp
        src/Controllers/DriveWaypointController.cpp
        src/DriveSubsystem.cpp
        src/GearPickupSubsystem.cpp
        src/GearSubsystem.cpp
        src/HopperSubsystem.cpp
        src/Robot.cpp
        src/VisionSubsystem.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} CORERobotLib CTRE NAVX-MXP WPILIB seasocks JSON)
