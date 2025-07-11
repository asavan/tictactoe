cmake_minimum_required(VERSION 3.16)
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_DISABLE_PRECOMPILE_HEADERS ON)
add_compile_options(/W4 /WX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_executable(tictactoe WIN32 windows.cpp button.cpp dialog.rc resource.h button.h)
# target_link_libraries(tictactoe user32 gdi32 kernel32)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${ProjectId})
target_compile_definitions(tictactoe PRIVATE UNICODE _UNICODE)
