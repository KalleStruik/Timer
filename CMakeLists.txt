cmake_minimum_required(VERSION 3.17)
project(Timer)

set(CMAKE_CXX_STANDARD 14)

# Find includes in the build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Turn on automatic invocation of the MOC, UIC & RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

find_package(Qt5 REQUIRED COMPONENTS Widgets)

add_executable(Timer src/main.cpp src/MainWindow.cpp src/MainWindow.h src/TimerThread.cpp src/TimerThread.h src/Structs.h src/config.h)

target_link_libraries(Timer Qt5::Widgets)