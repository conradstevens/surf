cmake_minimum_required(VERSION 3.29)
set(CMAKE_CXX_STANDARD 20)

project(surf)


# Executables
add_executable(${PROJECT_NAME}
        # lib headers
        # My files
        src/main.cpp
        # Entities
            include/entities/entity.h
                src/entities/entity.cpp
            include/entities/ball.h
                src/entities/ball.cpp
            include/entities/snow_flake.h
                src/entities/snow_flake.cpp
            include/entities/loc.h

        # Rendering
            include/rendering/glfw_ancillary.h
                src/rendering/glfw_ancillary.cpp
            include/rendering/mesh.h
                src/rendering/mesh.cpp
            include/rendering/shader.h
            include/rendering/mesh_loader.h

        # Scene
            include/scenes/scene.h
                src/scenes/scene.cpp
            include/scenes/snow_scene.h
                src/scenes/snow_scene.cpp
)


# Include
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/lib/include/)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include/)

# Local Binaries
target_link_libraries(${PROJECT_NAME}
        ${CMAKE_SOURCE_DIR}/lib/binaries/GLFW/libglfw.3.4.dylib  # Cannot build static library
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
        "-framework CoreFoundation"
)

find_package(Eigen3 3.3 REQUIRED)
target_link_libraries(${PROJECT_NAME} Eigen3::Eigen)