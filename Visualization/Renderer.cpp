#include "Renderer.hpp"

void Renderer::draw(unsigned int width,
                   unsigned int height,
                   const glm::mat4 &view,
                   const GLfloat fov)
{
    if (_depthShader) {
        drawDepthCubemap();
        glViewport(0, 0, width, height);
    }

    glClearColor(_clearColor.x, _clearColor.y, _clearColor.z, _clearColor.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Projection:
    glm::mat4 projection;
    projection = glm::perspective(fov, static_cast<float>(width)
                                      / static_cast<float>(height),
                                  _near, _far);


    for (auto &object : _objects) {
        object->getShader()->Use();


        // Set light color:
        auto lightColorLoc = glGetUniformLocation(object->getShader()->getProgram(), "lightColor");
        glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);

        // Set ambient lighting:
        auto ambientFactorLoc =
            glGetUniformLocation(object->getShader()->getProgram(), "ambientFactor");
        glUniform1f(ambientFactorLoc, 0.2f);

        glUniform1f(glGetUniformLocation(object->getShader()->getProgram(), "far_plane"), _far);
        auto lightPos = _lightSources[0]->getPosition();
        glUniform3fv(glGetUniformLocation(object->getShader()->getProgram(), "lightPos"),
                     1,
                     &lightPos[0]);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, _depthCubemap);

        drawObject(view, projection, object);
    }
}

void Renderer::drawObject(const glm::mat4 &view, const glm::mat4 &projection, Shape *&object) const
{
    GLint modelLoc = glGetUniformLocation(object->getShader()->getProgram(), "model");
    GLint viewLoc = glGetUniformLocation(object->getShader()->getProgram(), "view");
    GLint projectionLoc = glGetUniformLocation(object->getShader()->getProgram(),
												   "projection");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE,
						   glm::value_ptr(projection));

    auto colorLocation = glGetUniformLocation(object->getShader()->getProgram(), "uniColor");
    glUniform3fv(colorLocation, 1, glm::value_ptr(object->getColor()));

    object->Draw(modelLoc);
}

void Renderer::setupDepthShaderSettings()
{
    glGenTextures(1, &_depthCubemap);
    glGenFramebuffers(1, &_depthMapFBO);

    glBindTexture(GL_TEXTURE_CUBE_MAP, _depthCubemap);
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
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, _depthCubemap, 0);
    glDrawBuffer(GL_NONE); // Do not render to any color buffer.
    glReadBuffer(GL_NONE);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Framebuffer not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::drawDepthCubemap()
{
    auto shadowProj =
            glm::perspective(
                90.0f, static_cast<GLfloat>(_shadowWidth) / static_cast<GLfloat>(_shadowHeight),
                _near, _far
            );

    auto lightPos = _lightSources[0]->getPosition();
    std::vector<glm::mat4> shadowTransforms = getCubeViewMatrices(shadowProj, lightPos);

    glViewport(0, 0, _shadowWidth, _shadowHeight);
    glBindFramebuffer(GL_FRAMEBUFFER, _depthMapFBO);
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

    for (auto &object : _objects) {
        object->Draw(modelLoc);
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
