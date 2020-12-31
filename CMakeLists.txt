cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

set(IO_BUFFER_SOURCES
    src/io_file_reader.cpp
    src/io_file_writer.cpp
    src/io_memory_buffer.cpp
    src/char_stream.cpp
)

set(PUBLIC_HEADERS
    include/io-buffer.h
)

#--------------
# Static library
#--------------

project(io-buffer VERSION 0.1.2 DESCRIPTION "io buffer")

add_library(${PROJECT_NAME} STATIC ${IO_BUFFER_SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION 1)
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER ${PUBLIC_HEADERS})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "io-buffer")
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS -fPIC)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PRIVATE src)

install(FILES ${PUBLIC_HEADERS} DESTINATION include)

install (TARGETS ${PROJECT_NAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    PUBLIC_HEADER DESTINATION include
    COMPONENT library
)

#--------
# TESTS
#--------

project(io-buffer-tests)

set(CMAKE_BUILD_TYPE Debug)

include_directories(
    include
    /usr/local/include
)

find_library(CPP_UNIT_TEST libcpp-unit-test.a)
message(STATUS "Found cpp-unit-test: ${CPP_UNIT_TEST}")

add_executable(
    ${PROJECT_NAME} tests/tests.cpp
    ${IO_BUFFER_SOURCES}
)

target_link_libraries(${PROJECT_NAME}
    ${CPP_UNIT_TEST}
)
