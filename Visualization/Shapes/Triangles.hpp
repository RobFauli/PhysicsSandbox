#ifndef PHYSICSSANDBOX_TRIANGLES_HPP
#define PHYSICSSANDBOX_TRIANGLES_HPP


#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <algorithm>
#include <Tools/TransformationMatrices.hpp>

#include "Shape.hpp"


class Triangles : public Shape {
public:
	virtual ~Triangles() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}

	virtual GLuint getVAO() override { return VAO; };

	Triangles(const std::vector<GLfloat> vertices, const std::vector<GLuint> indices, const Shader *shader,
			  std::vector<glm::vec3> positions)
			: _vertices(vertices), _indices(indices), _positions(positions), _shader(shader) { }

	virtual void Setup(GLFWwindow *windowcontext) override {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		Setup();
	}
	void Setup();

	virtual void Draw(GLint modelLoc) override;

	virtual const std::vector<glm::vec3> &getPositions() override {
		return _positions;
	}

    virtual const std::vector<GLfloat> &getRotations() override {
		return _rotations;
	}

    virtual const std::vector<glm::mat4> & getModelMatrices() override
    {
        return _modelMatrices;
    }

    virtual const Shader *getShader() override {
		return _shader;
	}

    // This could be confusing, need to have a look at this.
    // It resets rotations to zero if used to change positions.
    // TODO Clarify this interface.
	void setPositions(const std::vector<glm::vec3> &positions) {
		_positions = positions;
        _rotations = std::vector<GLfloat>(_positions.size());
        for (const auto &position : _positions) {
            _modelMatrices.push_back(genModelMatrix(position));
        }
	}

	auto addObject(const glm::vec3 &position,
                   const glm::vec3 &rotateAlong = glm::vec3(0, 0, 0),
                   const GLfloat radiansRotated = 0)
    {
		_positions.push_back(position);
        _rotations.push_back(radiansRotated);
        auto model = genModelMatrix(position, rotateAlong, radiansRotated);
        _modelMatrices.push_back(model);

        return _modelMatrices.size() - 1;
	}

	void addObject(const glm::vec3 &position, GLfloat angleRotated)
    {
		_positions.push_back(position);
        _rotations.push_back(angleRotated);
	}

    void rotateObject(unsigned int i, glm::vec3 rotateAlong, GLfloat radians) {
        _rotations[i] += radians;
        _modelMatrices[i] = glm::rotate(_modelMatrices[i], radians, rotateAlong);
    }

	void resizeByFactor(GLfloat factor) {
		int count = 0;
		std::for_each(_vertices.begin(), _vertices.end(), [&count, factor](GLfloat &x) {
			if (count < 3) x *= factor; else; if (count == 5) count = 0; else ++count;});
	}

    virtual void setColor(float r, float g, float b) {
        _color = glm::vec3(r, g, b);
    }

    virtual const glm::vec3 &getColor() {
        return _color;
    }

protected:
	Triangles() { };

	GLuint VAO, VBO, EBO;
	std::vector<GLfloat> _vertices;
	std::vector<GLuint> _indices;
	std::vector<glm::vec3> _positions; // Position in world coordinates of all objects.
	std::vector<GLfloat> _rotations;
    std::vector<glm::mat4> _modelMatrices;
	const Shader *_shader;

	glm::vec3 _color; // Color of all triangles.

	virtual void setVertexAttributes() const;
};

#endif //PHYSICSSANDBOX_TRIANGLES_HPP
