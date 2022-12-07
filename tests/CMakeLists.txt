cmake_minimum_required(VERSION 3.10)

project(MinesweeperTest LANGUAGES CXX)

set(TEST_SOURCES
        src/main.cpp
        src/common_test_fixture.cpp
        src/field_manager_test.cpp
        src/field_test.cpp
        src/field_uncoverer_test.cpp
        src/minefield_test.cpp
        src/mines_generation_test.cpp)

add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(MinesweeperTest_run ${TEST_SOURCES} ${RESOURCE_FILES_DIR}/images.qrc)
target_include_directories(MinesweeperTest_run PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_link_libraries(MinesweeperTest_run gtest gtest_main libMinesweeper)