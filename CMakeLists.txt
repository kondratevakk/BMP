cmake_minimum_required(VERSION 3.26)
project(labwork3)

set(CMAKE_CXX_STANDARD 20)

add_executable(labwork3 main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE parsingFile parsingArg bmp)
add_subdirectory(parsingArg)
add_subdirectory(bmp)
add_subdirectory(parsingFile)
