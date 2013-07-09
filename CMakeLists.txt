project(candyboxgui)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(VERSION_MAJOR 1)
set(VERSION_MINOR 3.1BETA)
set(LIBRARY_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})
include_directories("src/")
add_definitions(-std=c++11) 

configure_file(
  "${PROJECT_SOURCE_DIR}/src/Config.hpp.in"
  "${PROJECT_SOURCE_DIR}/src/Config.hpp"
)

find_package(Qt5Core)

file(GLOB_RECURSE SRCS src/*.cpp)
if(CMAKE_BUILD_TYPE MATCHES Release)
	add_executable(${PROJECT_NAME} WIN32 ${SRCS})
else()
	add_executable(${PROJECT_NAME} ${SRCS})
endif()

qt5_use_modules(${PROJECT_NAME} Core Gui Widgets WebKit WebKitWidgets)
