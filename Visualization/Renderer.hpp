#ifndef PHYSICSSANDBOX_RENDERER_HPP
#define PHYSICSSANDBOX_RENDERER_HPP

#include <GL/glew.h>
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
	Renderer(
        glm::vec4 clearColor)
        : _shader(Shader(_vertexPath.c_str(), _geometryPath.c_str(), _fragmentPath.c_str())),
          _clearColor(clearColor),
          _depthShader(std::make_shared<Shader>(
              Shader("../../Visualization/Shaders/Shadow/Omnidirectional/OmniDirVertexShader.glsl",
    "../../Visualization/Shaders/Shadow/Omnidirectional/OmniDirGeometryShader.glsl",
    "../../Visualization/Shaders/Shadow/Omnidirectional/OmniDirFragmentShader.glsl")))
    {
        glGenFramebuffers(1, &_depthMapFBO);
    }
    void initialize();
	void draw(unsigned int width, unsigned int height, const glm::mat4 &view, const GLfloat fov)
    {
        _width = width; _height = height; _view = view; _fov = fov;
        draw();
    }
    void draw();
	void addObject (std::shared_ptr<Shape> object) {
		//object->Setup(_window.get());
        object->Setup();
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

    void removeAllShapes() {
        _objects.clear();
    }

    void setHeigh(GLint height)
    {
        _height = height;
    }
    void setWidth(GLint width)
    {
        _width = width;
    }
    void setFOV(GLfloat fov)
    {
        _fov = fov;
    }
    void setView(glm::mat4 view)
    {
        _view = view;
    }
    void setClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat w)
    {
        _clearColor = glm::vec4(r, g, b, w);
    }


private:
    GLint _width;
    GLint _height;
    GLfloat _fov;
    glm::mat4 _view;
    GLfloat _near = 1.0f;
    GLfloat _far = 250.0f;

	std::vector<std::shared_ptr<Shape>> _objects;
    std::string _vertexPath = "../../Visualization/Shaders/VertexShader.glsl";
    std::string _geometryPath = "../../Visualization/Shaders/GeometryShader.glsl";
    std::string _fragmentPath = "../../Visualization/Shaders/FragmentShader.glsl";
    Shader _shader;
    std::vector<std::shared_ptr<LightSource>> _pointLightSources;
    glm::vec4 _clearColor;

    // Shadow rendering settings:
    GLuint _shadowWidth = 1024;
    GLuint _shadowHeight = 1024;
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
