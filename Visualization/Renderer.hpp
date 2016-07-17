#ifndef PHYSICSSANDBOX_RENDERER_HPP
#define PHYSICSSANDBOX_RENDERER_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <map>

#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

#include "Shaders/Shader.hpp"
#include "Shapes/Shape.hpp"
#include "Shapes/LightSource.hpp"

class Renderer {
public:
	Renderer() { };
	Renderer(GLFWwindow *window, glm::vec4 clearColor)
        : _window(window), _clearColor(clearColor),
          _depthShader(std::make_unique<Shader>(
              Shader("../../Visualization/Shaders/Shadow/Omnidirectional/OmniDirVertexShader.glsl",
    "../../Visualization/Shaders/Shadow/Omnidirectional/OmniDirGeometryShader.glsl",
    "../../Visualization/Shaders/Shadow/Omnidirectional/OmniDirFragmentShader.glsl")))
    {
        glGenFramebuffers(1, &_depthMapFBO);
    }
	void draw(unsigned int width, unsigned int height, const glm::mat4 &view, const GLfloat fov);
	void addObject (Shape* object) {
		object->Setup(_window);
		_objects.push_back(object);
	}
    void addLightSource(LightSource* lightSource) {
        _pointLightSources.push_back(lightSource);
        _depthCubemaps.push_back(0);
        setupDepthShaderSettings();
    }
    void setupDepthShaderSettings();
    void drawDepthCubemaps();

    void setAmbientLightFactor(GLfloat factor) {
        _ambientLightFactor = factor;
    }

private:
	std::vector<Shape*> _objects;
    std::vector<LightSource*> _pointLightSources;
	GLFWwindow* _window;
	glm::vec4 _clearColor;

    // Shadow rendering settings:
    GLuint _shadowWidth = 1024;
    GLuint _shadowHeight = 1024;
    GLfloat _near = 1.0f;
    GLfloat _far = 250.0f;
    GLfloat _ambientLightFactor = 0.1;

    std::unique_ptr<Shader> _depthShader;
    GLuint _depthMapFBO;
    std::vector<GLuint> _depthCubemaps;

    void drawObject(const glm::mat4 &view, const glm::mat4 &projection, Shape *&object) const;
    std::vector<glm::mat4>
        getCubeViewMatrices(const glm::mat4 &shadowProj, const glm::vec3 &lightPos) const;
};


#endif //PHYSICSSANDBOX_RENDERER_HPP
