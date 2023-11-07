add_subdirectory(timer)
add_subdirectory(logger)
add_subdirectory(thread_pool)

add_library(utils INTERFACE)
target_link_libraries(utils INTERFACE timer fmt thread_pool)

target_include_directories(utils INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

