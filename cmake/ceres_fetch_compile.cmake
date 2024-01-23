cmake_minimum_required(VERSION 3.20)

if(NOT CERES_TARGET_VERSION)
    set(CERES_TARGET_VERSION 2.2.0)
endif()

include(FetchContent)
include(GNUInstallDirs)
set(FETCHCONTENT_QUIET  OFF)

FetchContent_Declare(
      ceres
      GIT_REPOSITORY https://github.com/ceres-solver/ceres-solver.git
      GIT_TAG ${CERES_TARGET_VERSION}
)

if(NOT ceres_POPULATED)
    message("Fetch ceres")
    FetchContent_Populate(ceres)
    set(MINIGLOG ON)
    set(BUILD_EXAMPLES OFF)
    set(USE_CUDA OFF)
    message(install_prefix is ${CMAKE_INSTALL_PREFIX})
    set(PROVIDE_UNINSTALL_TARGET OFF)
    set(EXPORT_BUILD_DIR OFF)


    message("Fetch ceres to " ${ceres_SOURCE_DIR})
    add_subdirectory(${ceres_SOURCE_DIR} ${ceres_BINARY_DIR})
    message("Fetch ceres done")
endif()

#


