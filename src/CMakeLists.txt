cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)

project(HardwareAndSystemInformation LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 REQUIRED COMPONENTS 
	Core 
	Gui 
	Widgets 
	WebEngineWidgets
)
	
set(project_headers 
	aboutwindow.h 
	datacollector.h 
	filesystemworkmodule.h 
	mainwindow.h 
	outerfileincluder.h
)
	
set(project_sources 
	aboutwindow.cpp 
	datacollector.cpp 
	filesystemworkmodule.cpp 
	main.cpp 
	mainwindow.cpp 
	outerfileincluder.cpp
)

qt5_wrap_cpp(project_sources_moc ${project_headers})

source_group("MOC Files" FILES ${project_sources_moc})

add_executable(${PROJECT_NAME} WIN32 
	${project_headers} 
	${project_sources} 
	${project_sources_moc}
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
