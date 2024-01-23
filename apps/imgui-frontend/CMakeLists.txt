cmake_minimum_required(VERSION 3.2)
project(calib_ui_frontend)
set(CMAKE_CXX_STANDARD 17)

CPMAddPackage("gh:g-truc/glm#0.9.9.8")

file(GLOB_RECURSE calib_ui_frontend_SOURCE ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_library(calib_ui_frontend ${calib_ui_frontend_SOURCE})
target_link_libraries(calib_ui_frontend PUBLIC imgui_app_base glm)
target_include_directories(calib_ui_frontend PUBLIC ./include)

add_executable(test ./main.cpp)
target_link_libraries(test calib_ui_frontend)

message("copy shaders files to ${CMAKE_CURRENT_BINARY_DIR}")
file(COPY ${CMAKE_CURRENT_LIST_DIR}/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
