cmake_minimum_required(VERSION 2.8)
project(calib)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_INSTALL_PREFIX "./install")
set(CMAKE_BUILD_TYPE "Debug")
# set(CMAKE_BUILD_TYPE "Release")
# set(CMAKE_CXX_FLAGS_RELEASE "-O3 -fPIC")

set(OpenCV_DIR /opt/opencv/4.5.4/lib/cmake/opencv4)
find_package(OpenCV 4 REQUIRED)
find_package(Ceres REQUIRED)
find_package(Eigen3 REQUIRED)

add_subdirectory(3rdparty)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(apps)
