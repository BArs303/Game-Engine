cmake_minimum_required(VERSION 3.31.3)

#set project name
project(game-engine)

#choose default compiler by setting environmental variable
#output executable to root directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

file(GLOB SOURCES "source/*.c")

#add source files to your project
add_executable(${PROJECT_NAME} ${SOURCES})
#add header dirictory to your project
target_include_directories(${PROJECT_NAME} PRIVATE headers) 
