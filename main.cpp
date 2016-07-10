#include <memory>
#include <Shapes/Cube.hpp>

#include "Window.hpp"
#include "Shapes/IcoSphere.hpp"


int main()
{
    Window window(1484, 1024, "test", {0.f, 0.f, 0.f, 1.f});
    Shader shader
        ("../../Visualization/Shaders/VertexShader.glsl",
         "../../Visualization/Shaders/GeometryShader.glsl",
         "../../Visualization/Shaders/FragmentShader.glsl");

    Shader depthShader
        ("../../Visualization/Shaders/Shadow/Omnidirectional/OmniDirVertexShader.glsl",
         "../../Visualization/Shaders/Shadow/Omnidirectional/OmniDirGeometryShader.glsl",
         "../../Visualization/Shaders/Shadow/Omnidirectional/OmniDirFragmentShader.glsl");
    //window.getRenderer().setDepthShader(&depthShader);

    auto R = 4u;
    std::unique_ptr<Cube> cube = std::make_unique<Cube>(Cube(shader, 1.0f, 1.0f, 1.0f));
    std::unique_ptr<IcoSphere> sphere = std::make_unique<IcoSphere>(IcoSphere(shader, R));
    Shape* cube_ptr = &*cube;
    Shape* sphere_ptr = &*sphere;

    window.getRenderer().addObject(cube_ptr);
    cube->setPositions(std::vector<glm::vec3>{glm::vec3(-1.0f, 0.0f, 0.0f)});

    window.getRenderer().addObject(sphere_ptr);
    sphere->setPositions(std::vector<glm::vec3>{glm::vec3(4.0f, 0.0f, 0.0f)});
    sphere->addObject(glm::vec3(-3.0, 0.0f, 0.0f));

    cube->setColor(1.0f, 0.0f, 0.0f);
    sphere->setColor(0.0f, 0.0f, 1.0f);

    auto lightSource = LightSource(glm::vec3(0.0f, 0.0f, 0.0f));
    window.getRenderer().addLightSource(&lightSource);


    while (!window.WindowShouldClose()) {
        window.GameLoop();
        cube->rotateObject(0, glm::vec3(1.0f, 0.0f, 0.0f), 0.003);
        sphere->rotateObject(0, glm::vec3(1.0f, 0.0f, 0.0f), 0.003);
    }

    return 0;
}


