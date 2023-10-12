add_subdirectory(utils)


add_library(core ./core/core.cpp)
    
message(${CMAKE_CURRENT_LIST_DIR}/include)
target_include_directories(
    core PUBLIC
    ${CERES_INCLUDE_DIRS}
    ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries(
    core PUBLIC
    ${OpenCV_LIBS}
    ${CERES_LIBRARIES}
    utils
    Eigen3::Eigen
)

