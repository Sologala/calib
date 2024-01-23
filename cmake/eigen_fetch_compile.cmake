cmake_minimum_required(VERSION 3.12)

if(NOT EIGEN_TARGET_VERSION)
    set(EIGEN_TARGET_VERSION 3.4.0)
endif()

include(FetchContent)
set(FETCHCONTENT_QUIET  OFF)

FetchContent_Declare(
      Eigen
      URL https://gitlab.com/libeigen/eigen/-/archive/${EIGEN_TARGET_VERSION}/eigen-${EIGEN_TARGET_VERSION}.tar.gz
      # GIT_TAG ${EIGEN_TARGET_VERSION}
)

if(NOT eigen_POPULATED)
    message("Fetch eigen")
    FetchContent_Populate(eigen)
    message("Fetch eigen to " ${eigen_SOURCE_DIR})
endif()
message("Fetch eigen done")

add_subdirectory(${eigen_SOURCE_DIR} ${eigen_BINARY_DIR})

#


