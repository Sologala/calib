add_library(thread_pool INTERFACE)
target_include_directories(thread_pool INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
    $<INSTALL_INTERFACE:include>
)

# 设置库的安装路径
install(TARGETS thread_pool DESTINATION lib)
install(FILES ./thread_pool.hpp DESTINATION include)
