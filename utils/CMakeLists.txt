add_library(utils STATIC socket_utils.c)

target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
