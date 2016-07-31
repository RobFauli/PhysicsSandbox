#include "Renderer.hpp"

void Renderer::draw()
{
    if (_depthShader) {
        drawDepthCubemaps();
        glViewport(0, 0, _width, _height);
    }

    glClearColor(_clearColor.x, _clearColor.y, _clearColor.z, _clearColor.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Projection:
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(_fov), static_cast<float>(_width)
                                      / static_cast<float>(_height),
                                  _near, _far);


    for (auto &object : _objects) {
        _shader.Use();
        auto program = _shader.getProgram();

        // Set ambient lighting:
        const auto ambientFactorLoc = glGetUniformLocation(program, "ambientFactor");
        glUniform1f(ambientFactorLoc, _ambientLightFactor);

        glUniform1f(glGetUniformLocation(program, "far_plane"), _far);
        auto i = 0u;
        for (const auto pointLight : _pointLightSources) {
            glUniform3fv(
                glGetUniformLocation(program, ("pointLightPos[" + std::to_string(i) + "]").c_str()),
                         1, &(pointLight->getPosition()[0]));
            glUniform3fv(
                glGetUniformLocation(program, ("lightColors[" + std::to_string(i++) + "]").c_str()),
                         1, &(pointLight->getLightColor()[0]));
        }
        glUniform1ui(glGetUniformLocation(program, "nPointLights"), i);

        drawObject(_view, projection, object);
    }
}

void Renderer::drawObject(const glm::mat4 &view, const glm::mat4 &projection,
                          std::shared_ptr<Shape> &object) const
{
    GLint modelLoc = glGetUniformLocation(_shader.getProgram(), "model");
    GLint viewLoc = glGetUniformLocation(_shader.getProgram(), "view");
    GLint projectionLoc = glGetUniformLocation(_shader.getProgram(),
												   "projection");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE,
						   glm::value_ptr(projection));

    auto colorLocation = glGetUniformLocation(_shader.getProgram(), "uniColor");
    glUniform3fv(colorLocation, 1, glm::value_ptr(object->getColor()));

    object->Draw(modelLoc);
}

void Renderer::setupDepthShaderSettings()
{
    const auto k = _depthCubemaps.size() - 1u;
    glGenTextures(1, &_depthCubemaps.back());
    glBindFramebuffer(GL_FRAMEBUFFER, _depthMapFBO);
    glActiveTexture(GL_TEXTURE0 + k);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _depthCubemaps.back());
    for (GLuint i = 0; i < 6; ++i) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT,
                     _shadowWidth, _shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindFramebuffer(GL_FRAMEBUFFER, _depthMapFBO);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, _depthCubemaps.back(), 0);
    glDrawBuffer(GL_NONE); // Do not render to any color buffer.
    glReadBuffer(GL_NONE);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Framebuffer not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    _shader.Use();
    glUniform1i(glGetUniformLocation(_shader.getProgram(),
                                     ("depthMaps[" + std::to_string(k) + "]").c_str()), k);
}

void Renderer::drawDepthCubemaps()
{
    const auto shadowProj =
            glm::perspective(
    glm::radians(90.0f), static_cast<GLfloat>(_shadowWidth) / static_cast<GLfloat>(_shadowHeight),
                _near, _far
            );

    glViewport(0, 0, _shadowWidth, _shadowHeight);
    glBindFramebuffer(GL_FRAMEBUFFER, _depthMapFBO);
    auto k = 0u;
    for (const auto &pointLightSource : _pointLightSources) {
        glActiveTexture(GL_TEXTURE0 + k++);
        auto lightPos = pointLightSource->getPosition();
        std::vector<glm::mat4> shadowTransforms = getCubeViewMatrices(shadowProj, lightPos);

        glClear(GL_DEPTH_BUFFER_BIT);
        _depthShader->Use();
        for (GLuint i = 0; i < 6; ++i)
            glUniformMatrix4fv(
                glGetUniformLocation(
                    _depthShader->getProgram(),
                    ("viewMatrices[" + std::to_string(i) + "]").c_str()),
                1, GL_FALSE, glm::value_ptr(shadowTransforms[i]));
        glUniform1f(glGetUniformLocation(_depthShader->getProgram(), "far_plane"), _far);
        glUniform3fv(glGetUniformLocation(_depthShader->getProgram(), "lightPos"), 1, &lightPos[0]);
        GLint modelLoc = glGetUniformLocation(_depthShader->getProgram(), "model");

        for (const auto &object : _objects) {
            object->Draw(modelLoc);
        }
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

std::vector<glm::mat4>
    Renderer::getCubeViewMatrices(const glm::mat4 &shadowProj, const glm::vec3 &lightPos) const
{
    std::vector<glm::mat4> shadowTransforms;
    shadowTransforms.push_back(shadowProj *
        lookAt(
            lightPos, lightPos + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    shadowTransforms.push_back(shadowProj *
        lookAt(
            lightPos, lightPos + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    shadowTransforms.push_back(shadowProj *
        lookAt(
            lightPos, lightPos + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
    shadowTransforms.push_back(shadowProj *
        lookAt(
            lightPos, lightPos + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
    shadowTransforms.push_back(shadowProj *
        lookAt(
            lightPos, lightPos + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    shadowTransforms.push_back(shadowProj *
        lookAt(
            lightPos, lightPos + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    return shadowTransforms;
}
void Renderer::initialize()
{
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW." << std::endl;
        exit(-1);
    }
    glEnable(GL_DEPTH_TEST);
}

