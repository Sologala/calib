add_library(frontend INTERFACE)
# target_link_libraries(frontend INTERFACE timer fmt)

target_include_directories(frontend INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

