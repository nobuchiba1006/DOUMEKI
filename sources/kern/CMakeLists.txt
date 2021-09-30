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

MESSAGE("entering kern cmake")

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

set(J4kern_src
	src/J4AttMFieldMap.cc
	src/J4Global.cc
	src/J4GlobalMessenger.cc
	src/J4MaterialCatalog.cc
	src/J4MFieldMapStore.cc
	src/J4Named.cc
	src/J4Object.cc
	src/J4ParameterListStore.cc
	src/J4SubtractionSolid.cc
	src/J4Timer.cc
	src/J4UnionSolid.cc
	src/J4VAcceleratorComponent.cc
	src/J4VComponent.cc
	src/J4VDetectorComponent.cc
	src/J4VHit.cc
	src/J4VisManager.cc
	src/J4VMaterialStore.cc
	src/J4VMField.cc
	src/J4VParameterList.cc
	src/J4VSensitiveDetector.cc
	src/J4VTrackerHit.cc
)

add_library(J4kern SHARED ${J4kern_src})

# List any source specific properties here

