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
	Renderer(std::shared_ptr<GLFWwindow> &window, glm::vec4 clearColor)
        : _window(window),
          _shader(Shader(_vertexPath.c_str(), _geometryPath.c_str(), _fragmentPath.c_str())),
          _clearColor(clearColor),
          _depthShader(std::make_shared<Shader>(
              Shader("../../Visualization/Shaders/Shadow/Omnidirectional/OmniDirVertexShader.glsl",
    "../../Visualization/Shaders/Shadow/Omnidirectional/OmniDirGeometryShader.glsl",
    "../../Visualization/Shaders/Shadow/Omnidirectional/OmniDirFragmentShader.glsl")))
    {
        glGenFramebuffers(1, &_depthMapFBO);
    }
	void draw(unsigned int width, unsigned int height, const glm::mat4 &view, const GLfloat fov);
	void addObject (std::shared_ptr<Shape> object) {
		object->Setup(_window.get());
		_objects.push_back(object);
	}
    void addLightSource(std::shared_ptr<LightSource> lightSource) {
        _pointLightSources.push_back(lightSource);
        _depthCubemaps.push_back(0);
        setupDepthShaderSettings();
    }
    void setupDepthShaderSettings();
    void drawDepthCubemaps();

    void setAmbientLightFactor(GLfloat factor) {
        _ambientLightFactor = factor;
    }

    void removeAllObjects() {
        _objects.clear();
    }

private:
	std::vector<std::shared_ptr<Shape>> _objects;
    std::string _vertexPath = "../../Visualization/Shaders/VertexShader.glsl";
    std::string _geometryPath = "../../Visualization/Shaders/GeometryShader.glsl";
    std::string _fragmentPath = "../../Visualization/Shaders/FragmentShader.glsl";
    Shader _shader;
    std::vector<std::shared_ptr<LightSource>> _pointLightSources;
	std::shared_ptr<GLFWwindow> _window;
	glm::vec4 _clearColor;

    // Shadow rendering settings:
    GLuint _shadowWidth = 1024;
    GLuint _shadowHeight = 1024;
    GLfloat _near = 1.0f;
    GLfloat _far = 250.0f;
    GLfloat _ambientLightFactor = 0.2;

    std::shared_ptr<Shader> _depthShader;
    GLuint _depthMapFBO;
    std::vector<GLuint> _depthCubemaps;

    void drawObject(const glm::mat4 &view, const glm::mat4 &projection,
                    std::shared_ptr<Shape> &object) const;
    std::vector<glm::mat4>
        getCubeViewMatrices(const glm::mat4 &shadowProj, const glm::vec3 &lightPos) const;
};


#endif //PHYSICSSANDBOX_RENDERER_HPP
