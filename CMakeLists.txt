project(candyboxgui)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(VERSION_MAJOR 1)
set(VERSION_MINOR 4.1)
set(LIBRARY_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})
if(NOT WIN32)
	if(NOT APP_DIRECTORY)
		set(APP_DIRECTORY "/usr/share/candyboxgui/")
	endif()
else()
	set(APP_DIRECTORY "./")
endif()

include_directories("src/")
add_definitions(-std=c++11) 
if(UNIX)
	IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    # Linux specific code
    SET(OPERATINGSYSTEM Linux)
	ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
elseif(WIN32)
	set(OPERATINGSYSTEM Win32)
	
endif()

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

if(UNIX)
	INSTALL(TARGETS ${PROJECT_NAME} DESTINATION bin)
	INSTALL(FILES ${QM_FILES} DESTINATION /usr/share/candyboxgui/translation)
	file(GLOB_RECURSE image image/*)
	INSTALL(FILES ${image} DESTINATION /usr/share/candyboxgui/image)
endif(UNIX)


