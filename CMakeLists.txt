project(candyboxgui)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(VERSION_MAJOR 1)
set(VERSION_MINOR 3.2BETA)
set(LIBRARY_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})
include_directories("src/")
add_definitions(-std=c++11) 

configure_file(
  "${PROJECT_SOURCE_DIR}/src/Config.hpp.in"
  "${PROJECT_SOURCE_DIR}/src/Config.hpp"
)

find_package(Qt5Core)
find_package(Qt5LinguistTools)

file(GLOB SRCS src/*.cpp)
file(GLOB HDRS src/*.hpp)
file (GLOB TRANSLATIONS_FILES translation/*.ts)

set(FILE_TO_TRANSLATE ${SRCS} ${HDRS})
if (UPDATE_TS_FILE)
  qt5_create_translation(QM_FILES ${FILE_TO_TRANSLATE} translation/candyboxgui_fr.ts)
else (UPDATE_TS_FILE)
  QT5_ADD_TRANSLATION(QM_FILES translation/candyboxgui_fr.ts)
endif (UPDATE_TS_FILE)

if(WIN32)
	if(CMAKE_BUILD_TYPE MATCHES Release)
		add_executable(${PROJECT_NAME} WIN32 ${SRCS} src/save/MainWinSave.cpp ${QM_FILES})
	else()
		add_executable(${PROJECT_NAME} ${SRCS} src/save/MainWinSave.cpp ${QM_FILES})
	endif()
else()
	add_executable(${PROJECT_NAME} ${SRCS} src/save/MainWinSave.cpp ${QM_FILES})
endif()

qt5_use_modules(${PROJECT_NAME} Core Gui Widgets WebKit WebKitWidgets)
