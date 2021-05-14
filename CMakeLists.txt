project(codemaster-cpp)

# CMake version >= 3.10 due to gtest_discover_tests()
# See https://cmake.org/cmake/help/git-stage/module/GoogleTest.html
cmake_minimum_required(VERSION 3.10)

include (CTest)
enable_testing()
find_package(Threads REQUIRED)
find_package(GTest REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${GTEST_INCLUDE_DIR})

aux_source_directory(${CMAKE_SOURCE_DIR}/src EXECUTABLE)
foreach(T_FILE_NAME ${EXECUTABLE})
    get_filename_component(EXECUTABLE_NAME ${T_FILE_NAME} NAME_WE)
    add_executable(${EXECUTABLE_NAME} ${T_FILE_NAME})
    target_link_libraries(
        ${EXECUTABLE_NAME}
        PRIVATE
        ${CMAKE_THREAD_LIBS_INIT}
        GTest::GTest
        GTest::Main
    )
    gtest_discover_tests(${EXECUTABLE_NAME})
endforeach()