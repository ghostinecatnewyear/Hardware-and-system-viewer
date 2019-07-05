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

add_executable(${PROJECT_NAME} 
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
