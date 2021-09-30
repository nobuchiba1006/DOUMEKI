#------------------------------------------------------------------------------
# CMakeLists.txt
# Module : kern
#
# CMakeLists.txt for building a single granular library.
#
# Generated on : 12/11/2014
#
# $Id: CMakeLists.txt 66892 2013-01-17 10:57:59Z hoshina$
#
#------------------------------------------------------------------------------

MESSAGE("entering exp cmake")

# List external includes needed.
include_directories(${CLHEP_INCLUDE_DIRS})

# List internal includes needed.
include_directories(${CMAKE_SOURCE_DIR}/source/global/management/include)
include_directories(${CMAKE_SOURCE_DIR}/source/intercoms/include)
include_directories(${CMAKE_SOURCE_DIR}/source/materials/include)
include_directories(${CMAKE_SOURCE_DIR}/source/geometry/magneticfield/include)
include_directories(${CMAKE_SOURCE_DIR}/source/geometry/volumes/include)
include_directories(${CMAKE_SOURCE_DIR}/source/geometry/management/include)
include_directories(${CMAKE_SOURCE_DIR}/source/geometry/solids/usolids/include)
include_directories(${CMAKE_SOURCE_DIR}/source/geometry/solids/Boolean/include)
include_directories(${CMAKE_SOURCE_DIR}/source/geometry/solids/CSG/include)
include_directories(${CMAKE_SOURCE_DIR}/source/geometry/solids/specific/include)
include_directories(${CMAKE_SOURCE_DIR}/source/event/include)
include_directories(${CMAKE_SOURCE_DIR}/source/digits_hits/detector/include)
include_directories(${CMAKE_SOURCE_DIR}/source/graphics_reps/include)
include_directories(${CMAKE_SOURCE_DIR}/source/visualization/management/include)

include_directories(${PROJECT_SOURCE_DIR}/sources/kern/include)
include_directories(${PROJECT_SOURCE_DIR}/sources/exp/include)

set(J4exp_src
	src/J4CAINEvtInterface.cc
	src/J4CAINEvtMessenger.cc
	src/J4CircleBeam.cc
	src/J4CircleBeamMessenger.cc
	src/J4DetectorConstruction.cc
	src/J4EventAction.cc
	src/J4EXPHall.cc
	src/J4HEPEvtInterface.cc
	src/J4HEPEvtMessenger.cc
	src/J4ParameterList.cc
	src/J4ParticleBeam.cc
	src/J4ParticleBeamMessenger.cc
	src/J4PhysicsList.cc
	src/J4PhysicsList.cc.orig
	src/J4PhysicsListMessenger.cc
	src/J4PrimaryGeneratorAction.cc
	src/J4PrimaryGeneratorMessenger.cc
	src/J4RunAction.cc
	src/J4RunActionMessenger.cc
	src/J4TrackingAction.cc
	src/J4TrackingActionMessenger.cc
)

add_library(J4exp SHARED ${J4exp_src})

# List any source specific properties here

