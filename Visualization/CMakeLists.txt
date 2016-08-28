set(Library_FILES
        Window.cpp
        Shaders/Shader.cpp
        Camera.cpp
        Renderer.cpp
        Input.cpp Shapes/IcoSphere.cpp Shapes/Triangles.cpp Shapes/Shape.cpp Shapes/Cube.cpp
        Shapes/LightSource.cpp Shapes/LightSource.hpp)

set(Shader_FOLDER Shaders)
set(Omni_FOLDER Shaders/Shadow/Omnidirectional)

set(Shader_FILES
    ${Shader_FOLDER}/VertexShader.glsl
    ${Shader_FOLDER}/GeometryShader.glsl
    ${Shader_FOLDER}/FragmentShader.glsl
    )

set(Omni_FILES # Folder with the shaders for omnidirectional shadows.
    ${Omni_FOLDER}/OmniDirVertexShader.glsl
    ${Omni_FOLDER}/OmniDirGeometryShader.glsl
    ${Omni_FOLDER}/OmniDirFragmentShader.glsl
    )

if (NOT CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR)
    foreach(item IN LISTS Shader_FILES)
        file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${item} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${Shader_FOLDER})
    endforeach()
    foreach(item IN LISTS Omni_FILES)
        file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${item} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${Omni_FOLDER})
    endforeach()
endif()

add_library(visualization ${Library_FILES})

target_link_libraries(visualization GL GLEW glfw)
target_include_directories(visualization PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
