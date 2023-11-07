cmake_minimum_required(VERSION 3.5)

project(calib_qt LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()
find_package(OpenGL REQUIRED)
find_package(Qt5 COMPONENTS Widgets OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})

add_subdirectory(./widget/QTPropertyEditor/)

add_executable(calib_qt
    main.cpp
    mainwindow.cpp
    mainwindow.h
    ./widget/points.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ui/mainwindow.ui
)

target_link_libraries(calib_qt PRIVATE 
    Qt5::Widgets
    Qt5::OpenGL 
    ${OPENGL_LIBRARIES}
    ${GLUT_LIBRARY}
    core
    utils
    PropertyEditor
)

# 查找 Shader 文件
file(GLOB SHADER_FILES shaders/*.*s)

# 设置 Shader 输出路径
set(SHADER_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/shaders")
foreach(SHADER_FILE ${SHADER_FILES})
    get_filename_component(SHADER_FILE_NAME ${SHADER_FILE} NAME)
    set(SHADER_OUTPUT "${SHADER_OUTPUT_DIR}/${SHADER_FILE_NAME}")
    add_custom_command(
        TARGET calib_qt POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            ${SHADER_FILE} ${SHADER_OUTPUT}
        COMMENT "Copying ${SHADER_FILE_NAME} to ${SHADER_OUTPUT}"
    )
endforeach()


