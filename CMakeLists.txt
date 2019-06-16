cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

set(IO_BUFFER_SOURCES
    src/io_file_reader.cpp
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

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME} PRIVATE src)

install (TARGETS ${PROJECT_NAME}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT library
)
