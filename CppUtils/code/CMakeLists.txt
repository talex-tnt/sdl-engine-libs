cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 11)

project (cpp-utils)

add_library(${PROJECT_NAME} INTERFACE)
add_library(sub::cpp-utils ALIAS ${PROJECT_NAME})

file(GLOB_RECURSE HEADER_FILES "include/*.h" "include/*.inl")
add_custom_target(${PROJECT_NAME}-h SOURCES ${HEADER_FILES}) # hack to see the project in vs

target_include_directories(${PROJECT_NAME}
    INTERFACE
        ${PROJECT_SOURCE_DIR}/include
)