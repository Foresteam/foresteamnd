cmake_minimum_required(VERSION 3.0.0)
project(foresteam2d VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(foresteam2d
    src/Vector.h
    src/Vector2.h
    src/Utils.h
    src/Matrix.h
    src/Quaternion.h
    
    src/Vector.cpp
    src/Vector2.cpp
    src/Utils.cpp
    src/Matrix.cpp
    src/Quaternion.cpp

    main.cpp
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
add_compile_options(--std=g++20)
include(CPack)