cmake_minimum_required(VERSION 2.8)
project(ARTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB_RECURSE SOURCE_FILES
    "src/*.hpp"
    "src/*.h"
    "src/*.cpp"
    "src/*.C"
    "src/*.c"
)

add_executable(ar_test ${SOURCE_FILES})

#set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

#find_package(OpenGL REQUIRED)
#find_package(SDL2 REQUIRED)
#find_package(SOIL REQUIRED)
#find_package(OpenCV2 REQUIRED)
find_package(OpenCV REQUIRED)

#include_directories(${OPENGL_INCLUDE_DIR})
#include_directories(${SDL2_INCLUDE_DIR})
#include_directories(${SOIL_INCLUDE_DIR})
#include_directories(${OpenCV2_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})

#target_link_libraries(TCC ${OPENGL_LIBRARIES} ${SDL2_LIBRARY} ${SOIL_LIBRARY})
#target_link_libraries(ar_test ${OpenCV2_LIBRARIES})
target_link_libraries(ar_test ${OpenCV_LIBS})
