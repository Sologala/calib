cmake_minimum_required(VERSION 2.8)
project(calib)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_INSTALL_PREFIX "./install")
# set(CMAKE_CXX_FLAGS_RELEASE "-O3 -fPIC")

find_package(OpenCV 4 REQUIRED)
find_package(Ceres REQUIRED)
find_package(Eigen3 REQUIRED)

add_subdirectory(src)
add_subdirectory(test)
