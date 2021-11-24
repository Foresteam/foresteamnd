cmake_minimum_required(VERSION 3.0.0)
project(foresteamnd VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_FILES
    src/Vector.h
    src/Vector2.h
    src/Utils.h
    src/Matrix.h
    src/Quaternion.h
    src/Triangle.h
    src/Stack.h
    src/Table.h
    
    src/Vector.cpp
    src/Vector2.cpp
    src/Utils.cpp
    src/Utils.tcc
    src/Matrix.cpp
    src/Quaternion.cpp
    src/Triangle.cpp
    src/Stack.tcc
    src/Table.tcc
)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    list(APPEND BUILD_FILES debugTest.cpp)
    add_executable(foresteamnd ${BUILD_FILES})
else()
    add_library(foresteamnd ${BUILD_FILES})
endif()


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
add_compile_options(--std=g++20)
include(CPack)