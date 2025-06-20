cmake_minimum_required(VERSION "3.31.6")
project(CSocketTest)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_subdirectory(utils)
add_subdirectory(client)
add_subdirectory(server)
