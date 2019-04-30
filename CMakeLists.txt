cmake_minimum_required (VERSION 2.6)
set (CMAKE_CXX_STANDARD 11)
project (Grafika)
set(APP_TARGET Grafika)

# GLFW
find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
link_libraries(${GLFW_LIBRARY_DIRS})

# opengl
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# glew
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

# assimp
find_package(ASSIMP REQUIRED)
include_directories(${ASSIMP_INCLUDE_DIRS})

include_directories(
        include
        include/Jokowi
        include/Maruf 
        include/Breakout
        lib
)

# stb image library
add_library(stb_image STATIC
        lib/stb_image/stb_image.cpp
)

# abstraction library
add_library(Jokowi STATIC 
        src/Jokowi/Renderer.cpp
        src/Jokowi/VertexBuffer.cpp
        src/Jokowi/IndexBuffer.cpp
        include/Jokowi/VertexBufferLayout.h
        src/Jokowi/VertexArray.cpp
        src/Jokowi/Shader.cpp
        src/Jokowi/Texture.cpp
        src/Jokowi/Particle.cpp
)

# Breakout game library
add_library(breakoutLib STATIC
        src/Breakout/game.cpp
        src/Breakout/shader.cpp
        src/Breakout/texture.cpp
        src/Breakout/resource_manager.cpp
        src/Breakout/particle_generator.cpp
)

# add_executable(explore1 src/explore1.cpp)
# target_link_libraries(
#         explore1
#         glfw
#         ${OPENGL_LIBRARIES}
#         ${GLEW_LIBRARIES}
#         Jokowi
#         stb_image
# )

add_executable(explore2 src/explore2.cpp)
target_link_libraries(
        explore2
        glfw
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        Jokowi
        stb_image
)

# add_executable(explore3 src/explore3.cpp)
# target_link_libraries(
#         explore3
#         glfw
#         ${OPENGL_LIBRARIES}
#         ${GLEW_LIBRARIES}
#         ${ASSIMP_LIBRARIES}
#         Jokowi
#         stb_image
# )

add_executable(green_pentagon green_pentagon.cpp)
target_link_libraries(
        green_pentagon
        glfw
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        Jokowi
)

add_executable(pentagon pentagon.cpp)
target_link_libraries(
        pentagon
        glfw
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        Jokowi
)

add_executable(unicorn unicorn.cpp)
target_link_libraries(
        unicorn
        glfw
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        Jokowi
)

add_executable(jeep jeep.cpp)
target_link_libraries(
        jeep
        glfw
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${ASSIMP_LIBRARIES}
        Jokowi
        stb_image
)

# add_executable(lighting src/lighting.cpp)
# target_link_libraries(
#         lighting
#         glfw
#         ${OPENGL_LIBRARIES}
#         ${GLEW_LIBRARIES}
#         Jokowi
#         stb_image
# )

add_executable(uas uas.cpp)
target_link_libraries(
        uas
        glfw
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${ASSIMP_LIBRARIES}
        stb_image
        Jokowi
        breakoutLib
)

