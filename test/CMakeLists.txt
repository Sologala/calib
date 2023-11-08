
find_package(GTest REQUIRED)

link_libraries(calib::core calib::utils)
link_libraries(GTest::gtest GTest::gtest_main)
add_executable(test_base_type test_base_type.cpp)
target_compile_definitions(test_base_type PRIVATE 
    DATA_FOLDER="${CMAKE_CURRENT_LIST_DIR}/data"
    )
add_executable(test_capture ./capture.cpp)
add_executable(test_stereo ./test_cv_stereo_matching.cpp)
add_executable(test_checkboard_detect ./test_checkboard_detect.cpp)
add_executable(test_create_churo_board ./create_cv_churo_board.cpp)
add_executable(test_curve_fit ./test_curve_fit.cpp)

