file(GLOB_RECURSE TEST_SOURCES "*.cpp")
add_executable(EngineTests ${TEST_SOURCES})

target_link_libraries(EngineTests PRIVATE
    engine
    GTest::gtest
    GTest::gtest_main
)

target_include_directories(EngineTests PRIVATE
    ${CMAKE_SOURCE_DIR}/engine
)