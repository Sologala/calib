cmake_minimum_required(VERSION 3.12)
project(calibadd_executble)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_BUILD_TYPE "Release")
# set(CMAKE_BUILD_TYPE "Release") set(CMAKE_CXX_FLAGS_RELEASE "-O3 -fPIC")

if(MINGW)
  message("use MINGEW")
  add_compile_options(-Wa,-mbig-obj,-O2)
  add_compile_options(-std=c++17)
  set(CMAKE_CXX_FLAGS -O2)
endif()

if(NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)
    file(DOWNLOAD https://github.com/cpm-cmake/CPM.cmake/releases/latest/download/get_cpm.cmake ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)
endif()

include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)

include(./cmake/eigen_fetch_compile.cmake)

# cmake-format: off
CPMAddPackage(
  NAME ceres
  GITHUB_REPOSITORY ceres-solver/ceres-solver
  GIT_TAG 2.1.0
  OPTIONS
      "MINIGLOG ON"
      "USE_CUDA OFF"
      "BUILD_EXAMPLES OFF"
      "BUILD_TESTING OFF"
      "BUILD_BENCHMARKS OFF"
      "PROVIDE_UNINSTALL_TARGET OFF"
      "EXPORT_BUILD_DIR OFF"
      "EXCLUDE_FROM_ALL ON"
)

CPMAddPackage("gh:fmtlib/fmt#7.1.3")
CPMAddPackage(
  GITHUB_REPOSITORY gabime/spdlog
  VERSION 1.8.2
  OPTIONS "SPDLOG_FMT_EXTERNAL 1"
)
CPMAddPackage("gh:nlohmann/json@3.10.5")
CPMAddPackage("gh:Sologala/imgui-app-base#master")
CPMAddPackage(
  NAME googletest
  GITHUB_REPOSITORY google/googletest
  GIT_TAG release-1.8.1
  VERSION 1.8.1
  OPTIONS
      "INSTALL_GTEST OFF"
      "gtest_force_shared_crt ON"
)
# cmake-format: on

set(OpenCV_DIR ${CMAKE_CURRENT_LIST_DIR}/3rdparty/scripts/opencv-build/build)
find_package(OpenCV 4 REQUIRED)
# find_package(Ceres 4 REQUIRED)

# add_subdirectory(imgui-frontend)
 
add_executable(hhh aa.cpp)
target_link_libraries(hhh PRIVATE Eigen3::Eigen core)

# link_libraries(${OpenCV_LIBS})
# # find_package(Ceres REQUIRED) find_package(Eigen3 REQUIRED)
# # add_subdirectory(3rdparty)
add_subdirectory(apps)
add_subdirectory(src)
add_subdirectory(test)
