add_library(thread_pool INTERFACE)
target_include_directories(thread_pool INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
    $<INSTALL_INTERFACE:include>
)

# 设置库的安装路径
install(TARGETS thread_pool DESTINATION lib)


set(COMPONENT_NAME thread_pool)

install(
  TARGETS ${COMPONENT_NAME}
  EXPORT ${COMPONENT_NAME}Config
  ARCHIVE
  LIBRARY
  COMPONENT ${COMPONENT_NAME}
)

install(FILES ./thread_pool.hpp DESTINATION ${PROJECT_NAME}/include)

install(
  EXPORT ${COMPONENT_NAME}Config
  DESTINATION lib/cmake/${PROJECT_NAME}
  NAMESPACE ${PROJECT_NAME}::
  FILE ${COMPONENT_NAME}Config.cmake
  COMPONENT ${COMPONENT_NAME}
)

