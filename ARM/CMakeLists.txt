set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(WPILIB_HOME $ENV{HOME}/wpilib/cpp/current)
set(PROJECT_NAME "ARM_${PROJECT_NAME}")

set(CORERobotLib ${PROJECT_SOURCE_DIR}/../CORERobotLib)

set(CMAKE_C_COMPILER /usr/bin/arm-frc-linux-gnueabi-gcc)
set(CMAKE_CXX_COMPILER /usr/bin/arm-frc-linux-gnueabi-g++)

include_directories(${CORERobotLib}/3rdparty/CANTalon/include)
link_directories(${CORERobotLib}/3rdparty/CANTalon/lib)
include_directories(${CORERobotLib}/3rdparty/NavX/include)
link_directories(${CORERobotLib}/3rdparty/NavX/lib)

include_directories(${WPILIB_HOME}/include)
link_directories(${WPILIB_HOME}/lib)

include_directories(${CORERobotLib})
include_directories(${CORERobotLib}/src)

# For quick list run
# find src -iname "*.cpp"
# in project root
set(SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/Robot.cpp
        ${PROJECT_SOURCE_DIR}/src/DriveSubsystem.cpp
        ${PROJECT_SOURCE_DIR}/src/Autonomous/DriveForwardAuton.cpp
        ${CORERobotLib}/src/COREAuton.cpp
        ${CORERobotLib}/src/COREDrive.cpp
        ${CORERobotLib}/src/COREHardware/COREEncoder.cpp
        ${CORERobotLib}/src/COREHardware/COREJoystick.cpp
        ${CORERobotLib}/src/COREHardware/COREMotor.cpp
        ${CORERobotLib}/src/COREHardware/CORETimer.cpp
        ${CORERobotLib}/src/COREHardware/CORESensor.cpp
        ${CORERobotLib}/src/COREHardware.cpp
        ${CORERobotLib}/src/CORELog.cpp
        ${CORERobotLib}/src/COREPID.cpp
        ${CORERobotLib}/src/CORERobot.cpp
        ${CORERobotLib}/src/COREScheduler.cpp
        ${CORERobotLib}/src/COREDrive/CORESwerve.cpp
        ${CORERobotLib}/src/COREDashboard.cpp)

include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} libwpi.so libnavx_frc_cpp.a libTalonSRXLib.a)
