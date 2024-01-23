link_libraries(core utils)
link_libraries(gtest gtest_main gmock)
add_executable(test_logger ./test_logger.cpp)

# add_executable(test_capture ./capture.cpp)
# add_executable(test_stereo ./test_cv_stereo_matching.cpp)
# add_executable(test_checkboard_detect ./test_checkboard_detect.cpp)
# add_executable(test_create_churo_board ./create_cv_churo_board.cpp)
# add_executable(test_curve_fit ./test_curve_fit.cpp)
