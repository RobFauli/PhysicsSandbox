include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runPhysicsTests
        Vector3_test.cpp
        Force_test.cpp
        Simulation_test.cpp)

target_link_libraries(runPhysicsTests gtest gtest_main)
target_link_libraries(runPhysicsTests physics)
