add_executable(EngineTests ECS.cpp)

target_link_libraries(EngineTests PRIVATE
    engine
    gtest
    gtest_main
)

target_include_directories(EngineTests PRIVATE
    ${CMAKE_SOURCE_DIR}/engine
)