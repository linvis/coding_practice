cmake_minimum_required(VERSION 3.7.1)

project(APUE_thread)

message("build $SOURCE_FILE")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -W -g")

add_executable(test_pthread.o ${SOURCE_FILE})
