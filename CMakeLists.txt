cmake_minimum_required(VERSION 3.10)
project(tictactoe)

set(CMAKE_CXX_STANDARD 17)

add_executable(tictactoe WIN32 windows.cpp button.cpp dialog.rc resource.h button.h)
# target_link_libraries(tictactoe user32 gdi32 kernel32)
