//
// Created by robertfa on 17.03.16.
//

#ifndef PHYSICSSANDBOX_ICOSPHERE_HPP
#define PHYSICSSANDBOX_ICOSPHERE_HPP

// Std
#include <vector>
#include <cmath>
#include <iostream>

// GLEW
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// GLM Math
#include <glm/detail/func_exponential.hpp>

#include "Shape.hpp"
#include "Triangles.hpp"

auto convertarrayfromGLFloatTovec3(std::vector<GLfloat> vecOfFloats);
auto convertarrayfromVec3ToGLFloat(std::vector<glm::vec3> vecOfvec3);

void radialize(std::vector<GLfloat> &vertices, GLfloat radius);

class IcoSphere : public Triangles {
public:
	IcoSphere(const Shader &shader, unsigned int refinementLevel)
			: _refinementLevel(0), _radius(1.0) {
        _shader = &shader;
        GenerateIcosahedron();
		Refine(refinementLevel);
    };

	virtual ~IcoSphere() {
		// Parents destructor deletes the buffers.
	}

	void setRadius(GLfloat r) {
		_radius = r;
        radialize(_vertices, _radius);
	}


private:
    void Refine(unsigned int refinementLevel);
	void GenerateIcosahedron();
	unsigned int _refinementLevel;
	GLfloat _radius;
};



#endif //PHYSICSSANDBOX_ICOSPHERE_HPP
