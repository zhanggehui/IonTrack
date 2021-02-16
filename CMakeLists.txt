# Edep_grid TR_Track Stopping_power
set(P_NAME Projects/Edep_grid)

#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(IonTrack)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
#
include(${Geant4_USE_FILE})

option(CLUSTER_JOB "Run on beijixing cluster" ON)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file(${PROJECT_SOURCE_DIR}/RunConfig.h.in RunConfig.h)

#----------------------------------------------------------------------------
# Locate sources and headers for this project
#
include_directories(${PROJECT_BINARY_DIR}
                    ${PROJECT_SOURCE_DIR}/include 
                    ${PROJECT_SOURCE_DIR}/${P_NAME}/include
                    ${Geant4_INCLUDE_DIR})

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc
                  ${PROJECT_SOURCE_DIR}/${P_NAME}/src/*.cc)

file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh
                  ${PROJECT_SOURCE_DIR}/${P_NAME}/include/*.hh)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(IonTrack ${PROJECT_SOURCE_DIR}/${P_NAME}/main.cc ${sources} ${headers} ${TOOLS_FORTRAN_OBJECTS})
target_link_libraries(IonTrack ${Geant4_LIBRARIES} ${HBOOK_LIBRARIES})
