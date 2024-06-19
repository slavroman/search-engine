cmake_minimum_required(VERSION 3.23)

add_executable(GTests
        InvertedIndexTest.cpp
        SearchServerTest.cpp
        ${MY_SOURCE_PATH}/InvertedIndex.cpp
        ${MY_INCLUDE_PATH}/InvertedIndex.h
        ${MY_SOURCE_PATH}/SearchServer.cpp
        ${MY_INCLUDE_PATH}/SearchServer.h
        )

target_link_libraries(GTests gtest_main)

include(GoogleTest)

gtest_discover_tests(GTests)

target_include_directories(GTests PUBLIC ${MY_INCLUDE_PATH})
target_include_directories(GTests PUBLIC ${MY_SOURCE_PATH})