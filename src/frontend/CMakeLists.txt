add_library(frontend INTERFACE)
add_library(${PROJECT_NAME}::frontend ALIAS frontend)

# target_link_libraries(frontend INTERFACE timer fmt)
target_include_directories(frontend INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include>
)


