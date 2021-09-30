#---------------------------
# 1) Basic Configuration
#---------------------------

cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project (doumeki_dom)
project (doumeki_degg)
project (doumeki_megg)
project (doumeki_lom)

#root directory

include_directories(/proj/soft/ROOT/6.22.00/Install/include/)

#---------------------------
# 2) Find and Configure Geant4
#---------------------------

option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#---------------------------
# 3) Configure the Project to Use Geant4 and DOMINANT Headers
#---------------------------

include(${Geant4_USE_FILE})
#add_subdirectory(sources)

#---------------------------
# 4) Configure the Project to Use Geant4 and DOMINANT Headers
#---------------------------

include_directories(${PROJECT_SOURCE_DIR}/sources/kern/include)
include_directories(${PROJECT_SOURCE_DIR}/sources/exp/include)
include_directories(${PROJECT_SOURCE_DIR}/sources/parts/include)
include_directories(${PROJECT_SOURCE_DIR}/sources/dom/include)
include_directories(${PROJECT_SOURCE_DIR}/sources/degg/include)
include_directories(${PROJECT_SOURCE_DIR}/sources/megg/include)
include_directories(${PROJECT_SOURCE_DIR}/sources/lom/include)

#---------------------------
# 5) List the Sources to Build the Application 
#---------------------------

file(GLOB srcs ${PROJECT_SOURCE_DIR}/sources/*/src/*.cc)
file(GLOB hhs ${PROJECT_SOURCE_DIR}/sources/*/include/*.hh)

message(STATUS "  sources=${srcs}")
message(STATUS "  headers=${hhs}")

#---------------------------
# 6) Define and Link the Executable
#---------------------------

LINK_DIRECTORIES(/proj/soft/ROOT/6.22.00/Install/lib/)

add_executable(doumeki_dom Doumeki_DOM.cc ${srcs} ${hhs})
add_executable(doumeki_degg Doumeki_DEgg.cc ${srcs} ${hhs})
add_executable(doumeki_megg Doumeki_MEgg.cc ${srcs} ${hhs})
add_executable(doumeki_lom Doumeki_LOM.cc ${srcs} ${hhs})

target_link_libraries(doumeki_dom ${Geant4_LIBRARIES})
target_link_libraries(doumeki_degg ${Geant4_LIBRARIES})
target_link_libraries(doumeki_megg ${Geant4_LIBRARIES})
target_link_libraries(doumeki_lom ${Geant4_LIBRARIES})

# used for root environment
target_link_libraries(doumeki_dom ${Geant4_LIBRARIES} J4kern J4exp J4lom)
target_link_libraries(doumeki_dom Core Cint RIO Net Hist Graf Graf3d Gpad Tree Rint Postscript Matrix Physics MathCore Thread)

target_link_libraries(doumeki_degg ${Geant4_LIBRARIES} J4kern J4exp J4lom)
target_link_libraries(doumeki_degg Core Cint RIO Net Hist Graf Graf3d Gpad Tree Rint Postscript Matrix Physics MathCore Thread)

target_link_libraries(doumeki_megg ${Geant4_LIBRARIES} J4kern J4exp J4lom)
target_link_libraries(doumeki_megg Core Cint RIO Net Hist Graf Graf3d Gpad Tree Rint Postscript Matrix Physics MathCore Thread)

target_link_libraries(doumeki_lom ${Geant4_LIBRARIES} J4kern J4exp J4lom)
target_link_libraries(doumeki_lom Core Cint RIO Net Hist Graf Graf3d Gpad Tree Rint Postscript Matrix Physics MathCore Thread)



#---------------------------
# 7) Debug flag. Comment out for release.
#---------------------------

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D __THEBE__")

#---------------------------
# 8) Copy any Runtime Scripts to the Build Directory
#---------------------------

set(DOMINANT_SCRIPTS
    env.sh
    modify.sh
    README
    RELEASENOTE 
    )

foreach(_script ${DOMINANT_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

macro(configure_files srcDir destDir)
    message(STATUS "Configuring directory ${destDir}")
    make_directory(${destDir})

    file(GLOB templateFiles RELATIVE ${srcDir} ${srcDir}/*)
    foreach(templateFile ${templateFiles})
        set(srcTemplatePath ${srcDir}/${templateFile})
        if(NOT IS_DIRECTORY ${srcTemplatePath})
            message(STATUS "Configuring file ${templateFile}")
            configure_file(
                    ${srcTemplatePath}
                    ${destDir}/${templateFile}
                    @ONLY)
        elseif(IS_DIRECTORY ${srcTemplatePath})
            configure_files(${srcTemplatePath} ${destDir}/${templateFile})
        endif(NOT IS_DIRECTORY ${srcTemplatePath})
    endforeach(templateFile)
endmacro(configure_files)

configure_files(${PROJECT_SOURCE_DIR}/data
                ${PROJECT_BINARY_DIR}/data)

configure_files(${PROJECT_SOURCE_DIR}/tables
                ${PROJECT_BINARY_DIR}/tables)

configure_files(${PROJECT_SOURCE_DIR}/macros
                ${PROJECT_BINARY_DIR}/macros)

configure_files(${PROJECT_SOURCE_DIR}/scripts
                ${PROJECT_BINARY_DIR}/scripts)

configure_files(${PROJECT_SOURCE_DIR}/calc_acceptance
                ${PROJECT_BINARY_DIR}/calc_acceptance)

configure_files(${PROJECT_SOURCE_DIR}/submit
                ${PROJECT_BINARY_DIR}/submit)

configure_files(${PROJECT_SOURCE_DIR}/images
                ${PROJECT_BINARY_DIR}/images)

configure_files(${PROJECT_SOURCE_DIR}/seeds
                ${PROJECT_BINARY_DIR}/seeds)

configure_files(${PROJECT_SOURCE_DIR}/docs
                ${PROJECT_BINARY_DIR}/docs)

configure_files(${PROJECT_SOURCE_DIR}/examples
                ${PROJECT_BINARY_DIR}/examples)


 



