cmake_minimum_required(VERSION 3.23)

add_executable(SearchEngine
        main.cpp
        ConverterJSON.cpp
        InvertedIndex.cpp		
        SearchServer.cpp
        ${MY_INCLUDE_PATH}/ConverterJSON.h
        ${MY_INCLUDE_PATH}/ProjectExceptions.h
        ${MY_INCLUDE_PATH}/InvertedIndex.h
        ${MY_INCLUDE_PATH}/SearchServer.h)

target_include_directories(SearchEngine PUBLIC ${MY_INCLUDE_PATH})

file(COPY ../json DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY ../resources DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")