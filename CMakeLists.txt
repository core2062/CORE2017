cmake_minimum_required(VERSION 2.8)

project(CORE2017)

# Team number
set(TEAM_NUMBER 2062)

# Robot target
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g")

add_subdirectory(ARM)

set(WPILIB_HOME $ENV{HOME}/wpilib/cpp/current)
set(${PROJECT_NAME} ARM_${PROJECT_NAME})

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

#include_directories(${PROJECT_SOURCE_DIR}/3rdparty/CANTalon/include)
#include_directories(${PROJECT_SOURCE_DIR}/3rdparty/NavX/include)

include_directories(${PROJECT_SOURCE_DIR}/src/Fake_WPILib)
#include_directories(${WPILIB_HOME}/include)

# For quick list run
# find src -iname "*.cpp"
# in project root
set(SOURCE_FILES src/Robot.cpp)

# Deploy target

include_directories(src)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME})


#add_frc_deploy(deploy ${TEAM_NUMBER} $<TARGET_FILE:${PROJECT_NAME}>)
