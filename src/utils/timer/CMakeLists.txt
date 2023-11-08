add_library(timer STATIC
    ./src/timer.cpp
)
message(${CMAKE_CURRENT_LIST_DIR}/include)
target_include_directories(timer PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# 设置库的安装路径

set(COMPONENT_NAME timer)

install(FILES ./include/timer.hpp ./include/timer.hpp DESTINATION ${PROJECT_NAME}/include)

install(
  TARGETS ${COMPONENT_NAME}
  EXPORT ${COMPONENT_NAME}Config
  ARCHIVE
  LIBRARY
  COMPONENT ${COMPONENT_NAME}
)

install(
  EXPORT ${COMPONENT_NAME}Config
  DESTINATION lib/cmake/${PROJECT_NAME}
  NAMESPACE ${PROJECT_NAME}::
  FILE ${COMPONENT_NAME}Config.cmake
  COMPONENT ${COMPONENT_NAME}
)

