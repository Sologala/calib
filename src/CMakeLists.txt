add_subdirectory(utils)
add_subdirectory(backend)

add_library(core 
    ./core/core.cpp
    ./core/pattern_detect/opencv_checkboard.cpp
    )

add_library(${PROJECT_NAME}::core ALIAS core)
    
message(${CMAKE_CURRENT_LIST_DIR}/include)
target_include_directories(
    core PUBLIC
    ${CERES_INCLUDE_DIRS}
    ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries(
    core PUBLIC ${OpenCV_LIBS}
    ${CERES_LIBRARIES}
    calib::utils
    calib::backend
    Eigen3::Eigen
)
