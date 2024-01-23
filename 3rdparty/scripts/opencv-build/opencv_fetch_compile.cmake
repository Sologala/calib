cmake_minimum_required(VERSION 3.12)

if(NOT OPENCV_TARGET_VERSION)
    set(OPENCV_TARGET_VERSION 4.5.2)
endif()

include(FetchContent)
set(FETCHCONTENT_QUIET  OFF)

FetchContent_Declare(
      opencv_contrib
      GIT_REPOSITORY https://github.com/opencv/opencv_contrib.git
      GIT_TAG ${OPENCV_TARGET_VERSION}
)

if(NOT opencv_contrib_POPULATED)
    message("Fetch opencv_contrib")
    FetchContent_Populate(opencv_contrib)
    message("Fetch opencv_contrib to " ${opencv_contrib_SOURCE_DIR})
endif()
message("Fetch opencv_contrib done")

FetchContent_Declare(
      opencv
      GIT_REPOSITORY https://github.com/opencv/opencv.git
      GIT_TAG ${OPENCV_TARGET_VERSION}
)

if(NOT opencv_POPULATED)
    message("Fetch opencv " ${OPENCV_TARGET_VERSION})
    FetchContent_Populate(opencv)
    set(OPENCV_EXTRA_MODULES_PATH ${opencv_contrib_SOURCE_DIR}/modules)
    set(WITH_VTK OFF)
    set(BUILD_opencv_java OFF)
    set(BUILD_opencv_python OFF)
    set(BUILD_SHARED_LIBS OFF) # Build static opencv
    set(OPENCV_GENERATE_PKGCONFIG OFF) 
    set(WITH_LAPACK OFF) 
    # set(BUILD_TESTS OFF) 
    set(BUILD_PERF_TESTS OFF) 
    set(BUILD_EXAMPLES OFF) 
    # set(WITH_OPENGL ON)
    set(ENABLE_CXX11 ON)
    set(WITH_IPP OFF)
    set(ENABLE_PRECOMPILED_HEADERS OFF)
    set(WITH_OPENJPEG OFF)
    set(OPENCV_ENABLE_NONFREE ON)
    set(BUILD_opencv_python3 OFF)
    set(BUILD_opencv_python2 OFF)
    add_compile_options(-std=c++11)
    set(BUILD_opencv_wechat_qrcode OFF)
    # Bring the populated content into the build
    add_subdirectory(${opencv_SOURCE_DIR} ${opencv_BINARY_DIR})
endif()


