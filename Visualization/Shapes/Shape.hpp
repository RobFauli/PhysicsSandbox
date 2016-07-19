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
	virtual const glm::vec3 &getPosition() = 0;
	virtual const GLfloat &getRotation() = 0;
    virtual const glm::mat4 &getModelMatrix() = 0;
	virtual const Shader * getShader() = 0;
    virtual const glm::vec3 &getColor() = 0;

    virtual void setPosition(const GLfloat x, const GLfloat y, const GLfloat z) = 0;
    virtual void move(const GLfloat dx, const GLfloat dy, const GLfloat dz) = 0;
    virtual void rotate(GLfloat radians, glm::vec3 rotateAlong) = 0;
    virtual void rotate(GLfloat radians, GLfloat pivotX, GLfloat pivotY, GLfloat pivotZ) = 0;
};


#endif //PHYSICSSANDBOX_SHAPE_HPP
