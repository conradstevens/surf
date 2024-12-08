cmake_minimum_required(VERSION 3.29)
set(CMAKE_CXX_STANDARD 20)

project(surf)


# Executables
add_executable(${PROJECT_NAME}
        # lib headers
        include/opengl_rendering.h
        # My files
        src/main.cpp
        include/glfw_ancillary.h
        src/glfw_ancillary.cpp
        include/opengl_rendering.h
        src/opengl_rendering.cpp
        include/ball.h
        src/ball.cpp
        src/mesh.cpp
        src/mesh.h
)


# Include
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/lib/include/)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include/)


# Package Requirements
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)

find_package(GLEW REQUIRED)




# Local Binaries
target_link_libraries(${PROJECT_NAME}
        ${CMAKE_SOURCE_DIR}/lib/binaries/GLFW/libglfw.3.4.dylib  # Cannot build static library
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
        "-framework CoreFoundation"
)