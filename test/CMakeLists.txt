
find_package(GTest REQUIRED)


link_libraries(core)
link_libraries(GTest::gtest GTest::gtest_main)
add_executable(test_base_type test_base_type.cpp)
target_compile_definitions(test_base_type PRIVATE 
    DATA_FOLDER="${CMAKE_CURRENT_LIST_DIR}/data"
    )

