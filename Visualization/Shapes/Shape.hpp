//
// Created by robertfa on 19.03.16.
//

#ifndef PHYSICSSANDBOX_SHAPE_HPP
#define PHYSICSSANDBOX_SHAPE_HPP

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

#include <Shaders/Shader.hpp>
#include <glm/detail/type_mat.hpp>

class Shape {
public:
	virtual void Setup(GLFWwindow *) = 0;
	virtual GLuint getVAO() = 0;
	virtual void Draw(GLint modelLoc) = 0;
	virtual const std::vector<glm::vec3> & getPositions() = 0;
	virtual const std::vector<GLfloat> & getRotations() = 0;
    virtual const std::vector<glm::mat4> & getModelMatrices() = 0;
	virtual const Shader * getShader() = 0;
    virtual const glm::vec3 &getColor() = 0;
};


#endif //PHYSICSSANDBOX_SHAPE_HPP
