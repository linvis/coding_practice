cmake_minimum_required(VERSION 3.7.1)

project(APUE_process)

message("build $SOURCE_FILE")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -W -g -pthread")

add_executable(test_process.o ${SOURCE_FILE})
