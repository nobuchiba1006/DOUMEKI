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

MESSAGE("entering degg cmake")

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
include_directories(${PROJECT_SOURCE_DIR}/sources/degg/include)

set(J4degg_src
	src/J4DEgg.cc
	src/J4DEggGel.cc
	src/J4DEggGelHit.cc
	src/J4DEggGelSD.cc
	src/J4DEggInside.cc
	src/J4DEggParameterList.cc
	src/J4DEggShield.cc
)

add_library(J4degg SHARED ${J4degg_src})

# List any source specific properties here

