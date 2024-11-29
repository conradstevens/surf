cmake_minimum_required(VERSION 3.29)
project(surf)

set(CMAKE_CXX_STANDARD 20)


add_executable(${PROJECT_NAME}
        src/main.cpp
        include/head.h
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/lib/include/)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include/)

target_link_libraries(${PROJECT_NAME}
        ${CMAKE_SOURCE_DIR}/lib/binaries/GLFW/libglfw.3.4.dylib  # Cannot build static library
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
        "-framework CoreFoundation"
)