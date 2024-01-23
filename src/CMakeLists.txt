add_subdirectory(utils)
add_subdirectory(core)

# add_subdirectory(backend)

# add_library(core 
#     ./core/core.cpp
#     )
#
# add_library(${PROJECT_NAME}::core ALIAS core)
#    
# message(${CMAKE_CURRENT_LIST_DIR}/include)
# message(OpenCV_INCLUDE_DIRS)
# target_include_directories(
#     core PUBLIC
#     ${CERES_INCLUDE_DIRS}
#     ${OpenCV_INCLUDE_DIRS}
#     ${CMAKE_CURRENT_LIST_DIR}/include
# )
#
# target_link_libraries(
#     core PUBLIC
#     ${OpenCV_LIBS}
#     ${CERES_LIBRARIES}
#     # calib::utils
#     # calib::backend
#     Eigen3::Eigen
#     spdlog::spdlog
# )
