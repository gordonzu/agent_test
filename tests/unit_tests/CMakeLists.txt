include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(unit_tests_run
    test_xyenvironment.cpp
)

target_link_libraries(unit_tests_run gtest gtest_main)
target_link_libraries(unit_tests_run ${CMAKE_PROJECT_NAME}_lib)
