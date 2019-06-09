cmake_minimum_required(VERSION 3.7)

# compiler options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

project(io-buffer-tests)

find_library(IO_BUFFER libio-buffer.a)
message(STATUS "Found io-buffer library: ${IO_BUFFER}")

find_library(CPP_UNIT_TEST libcpp-unit-test.a)
message(STATUS "Found cpp-unit-test: ${CPP_UNIT_TEST}")

add_executable(${PROJECT_NAME} tests.cpp)

target_link_libraries(${PROJECT_NAME}
    ${IO_BUFFER}
    ${CPP_UNIT_TEST}
)
