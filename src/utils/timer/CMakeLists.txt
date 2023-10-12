add_library(timer STATIC
    ./src/timer.cpp
)
message(${CMAKE_CURRENT_LIST_DIR}/include)
target_include_directories(timer PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# 设置库的安装路径
install(TARGETS timer DESTINATION lib)
install(FILES ./include/timer.hpp ./include/timer.hpp DESTINATION include)

