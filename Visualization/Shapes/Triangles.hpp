#ifndef PHYSICSSANDBOX_TRIANGLES_HPP
#define PHYSICSSANDBOX_TRIANGLES_HPP


#include <vector>

#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <algorithm>
#include <Tools/TransformationMatrices.hpp>
#include <memory>

#include "Shape.hpp"


class Triangles : public Shape {
public:
	virtual ~Triangles() {
        if (buffersAndVertexArrayAllocated) {
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
            glDeleteBuffers(1, &EBO);
        }
	}

	virtual GLuint getVAO() override { return VAO; };

	Triangles(const std::vector<GLfloat> vertices,
              const std::vector<GLuint> indices,
              std::shared_ptr<Shader> shader,
              glm::vec3 position)
			: _vertices(vertices), _indices(indices), _position(position) { }

	virtual void Setup() override {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		buffersAndVertexArrayAllocated = true;
        subSetup();
	}
	void subSetup();

	virtual void Draw(GLint modelLoc) override;

	virtual const glm::vec3 &getPosition() override {
		return _position;
	}

    virtual const GLfloat &getRotation() override {
		return _rotation;
	}

    virtual const glm::mat4 &getModelMatrix() override
    {
        return _modelMatrix;
    }

    // This could be confusing, need to have a look at this.
    // It resets rotations to zero if used to change positions.
    // TODO Clarify this interface.
	void setPosition(const glm::vec3 &position) {
        _modelMatrix = glm::translate(_modelMatrix, position - _position);
		_position = position;
	}

    virtual void setPosition(const GLfloat x, const GLfloat y, const GLfloat z) override
    {
        auto pos = glm::vec3(x, y, z);
        setPosition(pos);
    }

    virtual void move(const GLfloat dx, const GLfloat dy, const GLfloat dz) override
    {
        _position += glm::vec3(dx, dy, dz);
    }

    virtual void rotate(GLfloat radians, glm::vec3 rotateAlong) override
    {
        _rotation += radians;
        _modelMatrix = glm::rotate(_modelMatrix, radians, rotateAlong);
    }

    virtual void rotate(GLfloat radians, GLfloat pivotX, GLfloat pivotY, GLfloat pivotZ) override
    {
        rotate(radians, glm::vec3(pivotX, pivotY, pivotZ));
    }

    void resizeByFactor(GLfloat factor) {
		int count = 0;
		std::for_each(_vertices.begin(), _vertices.end(), [&count, factor](GLfloat &x) {
			if (count < 3) x *= factor; else; if (count == 5) count = 0; else ++count;});
	}

    virtual void setColor(float r, float g, float b) override {
        _color = glm::vec3(r, g, b);
    }

    virtual const glm::vec3 &getColor() {
        return _color;
    }

protected:
	Triangles() { };

	GLuint VAO, VBO, EBO;
    bool buffersAndVertexArrayAllocated = false;
	std::vector<GLfloat> _vertices;
	std::vector<GLuint> _indices;
	glm::vec3 _position; // Position in world coordinates of all objects.
	GLfloat _rotation = 0.0f;
    glm::mat4 _modelMatrix;

	glm::vec3 _color; // Color of all triangles.

	virtual void setVertexAttributes() const;
};

#endif //PHYSICSSANDBOX_TRIANGLES_HPP
