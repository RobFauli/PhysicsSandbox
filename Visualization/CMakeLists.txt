set(Library_FILES
        Window.cpp
        Shaders/Shader.cpp
        Camera.cpp
        Renderer.cpp
        Input.cpp Shapes/IcoSphere.cpp Shapes/Triangles.cpp Shapes/Shape.cpp Shapes/Cube.cpp
        Shapes/LightSource.cpp Shapes/LightSource.hpp)

add_library(visualization ${Library_FILES})

target_link_libraries(visualization GL GLEW glfw)
target_include_directories(visualization PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})