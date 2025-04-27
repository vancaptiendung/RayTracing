cmake_minimum_required(VERSION 3.24)

project(raytracing)

set(CXX_FILE main.cpp)
set(UTIL_SOURCE)

file(GLOB UTIL_SOURCE CONFIGURE_DEPEND "./util/src")

list(APPEND CXX_FILE ${UTIL_SOURCE})

add_executable(${PROJECT_NAME} ${CXX_FILE})

include_directories(
    ../dependences/include/glm
    ./util
)
