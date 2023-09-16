cmake_minimum_required(VERSION 3.19)
project(Utils)
set(CMAKE_CXX_STANDARD 20)
file(GLOB SOURCES Source/* Source/**/*)
add_library(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
)