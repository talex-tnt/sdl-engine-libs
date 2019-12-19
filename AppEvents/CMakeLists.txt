cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 14)

include(utils)

get_folder_name(FOLDER_NAME)
project (${FOLDER_NAME})

file(GLOB_RECURSE HEADER_FILES "include/*.h" "include/*.inl")

create_groups("Header Files" "${CMAKE_CURRENT_SOURCE_DIR}/include" "${HEADER_FILES}")

add_library(${PROJECT_NAME} INTERFACE)
add_custom_target(${PROJECT_NAME}-h SOURCES ${HEADER_FILES}) # hack to see the project in vs

target_include_directories(${PROJECT_NAME}
    INTERFACE 
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
	INTERFACE
	AppUtils
)
