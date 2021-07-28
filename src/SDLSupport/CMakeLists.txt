cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 14)

include(utils)

get_folder_name(FOLDER_NAME)
project (${FOLDER_NAME})

collect_files(HEADER_FILES SOURCE_FILES)
group_files("${HEADER_FILES}" "${SOURCE_FILES}")

add_library(${PROJECT_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})

if( ${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    set(USE_FLAGS "-s USE_SDL=2")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXECUTABLE_SUFFIX .html)
endif()

target_link_libraries(${PROJECT_NAME}
   	${SDL2_LIBRARY}
	AppEvents
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${SDL2_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/include
	AppEvents
)
