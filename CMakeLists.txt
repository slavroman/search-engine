cmake_minimum_required(VERSION 3.23)

project(SearchEngine VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(MY_INCLUDE_PATH ${CMAKE_SOURCE_DIR}/include)
set(MY_SOURCE_PATH ${CMAKE_SOURCE_DIR}/src)

include(FetchContent)
include(GoogleTest)

FetchContent_Declare(
        googletest
        URL
        https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(gtest_disable_pthreads on)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(nlohmann_json)
add_subdirectory(src)
add_subdirectory(tests)

target_link_libraries(SearchEngine PRIVATE nlohmann_json::nlohmann_json)