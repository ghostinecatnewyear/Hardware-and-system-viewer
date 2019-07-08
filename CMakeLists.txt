cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)

project(HardwareAndSystemInformation LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS 
	Core 
	Gui 
	Widgets 
	WebEngineWidgets
)
	
set(project_headers 
	src/aboutwindow.h 
	src/datacollector.h 
	src/filesystemworkmodule.h 
	src/mainwindow.h 
	src/outerfileincluder.h 
	src/windowsoptions.h
)
	
set(project_sources 
	src/aboutwindow.cpp 
	src/datacollector.cpp 
	src/filesystemworkmodule.cpp 
	src/main.cpp 
	src/mainwindow.cpp 
	src/outerfileincluder.cpp 
	src/windowsoptions.cpp
)

set(project_resources resources.qrc)

qt5_wrap_cpp(project_mocs ${project_headers})
source_group("MOC Files" FILES ${project_mocs})

add_executable(${PROJECT_NAME} WIN32 
	${project_headers} 
	${project_sources} 
	${project_resources} 
	${project_mocs}
)

target_link_libraries(${PROJECT_NAME} PUBLIC 
	Qt5::Core 
	Qt5::Gui 
	Qt5::Widgets 
	Qt5::WebEngineWidgets
)

get_target_property(_qmake_executable Qt5::qmake IMPORTED_LOCATION)
get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_qt_bin_dir}")
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E
        env PATH="${_qt_bin_dir}" "${WINDEPLOYQT_EXECUTABLE}"
            --verbose 0
            --no-compiler-runtime
            \"$<TARGET_FILE:${PROJECT_NAME}>\"
)
