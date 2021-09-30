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

MESSAGE("entering dom cmake")

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
include_directories(${PROJECT_SOURCE_DIR}/sources/dom/include)

set(J4dom_src
	src/J4DOMBenthos.cc
	src/J4DOM.cc
	src/J4DOMGel.cc
	src/J4DOMHarness.cc
	src/J4DOMInside.cc
	src/J4DOMMainBoard.cc
	src/J4DOMMaterialStore.cc
	src/J4DOMParameterList.cc
	src/J4DOMPhotoCathode.cc
	src/J4DOMPMT.cc
	src/J4DOMPMTHit.cc
	src/J4DOMPMTSD.cc
	src/J4VDOMDetectorComponent.cc
)

add_library(J4dom SHARED ${J4dom_src})

# List any source specific properties here

