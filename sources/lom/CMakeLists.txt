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

MESSAGE("entering lom cmake")

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
include_directories(${PROJECT_SOURCE_DIR}/sources/lom/include)

set(J4lom_src
#	src/J4LOMShield.cc
	src/J4LOMOkamoto.cc
	src/J4LOMOkamotoHit.cc
	src/J4LOMOkamotoSD.cc
	src/J4LOM.cc
	src/J4LOMGel.cc
#	src/J4LOMGelHit.cc
#	src/J4LOMGelSD.cc
#	src/J4LOMHarness.cc
	src/J4LOMInside.cc
#	src/J4LOMInsideHit.cc
#	src/J4LOMInsideSD.cc
#	src/J4LOMMainBoard.cc
	src/J4LOMMaterialStore.cc
	src/J4LOMParameterList.cc
#	src/J4LOMPhotoCathode.cc
	src/J4LOMPMT.cc
	src/J4LOMPMTHit.cc
	src/J4LOMPMTSD.cc
#	src/J4LOMFlasher.cc
	src/J4LOMDetectorComponent.cc
)

add_library(J4lom SHARED ${J4lom_src})

# List any source specific properties here

