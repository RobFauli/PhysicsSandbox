#include "IcoSphere.hpp"

auto convertarrayfromGLFloatTovec3(std::vector<GLfloat> vecOfFloats) {
	std::vector<glm::vec3> vecOfglm;
	for (auto It = vecOfFloats.cbegin(); It != vecOfFloats.end(); It += 3) {
		vecOfglm.push_back(glm::vec3(*It, *(It + 1), *(It +2)));
	}
	return vecOfglm;
}

auto convertarrayfromVec3ToGLFloat(std::vector<glm::vec3> vecOfvec3)
{
	std::vector<GLfloat> vecOfFloats;
	for (auto It = vecOfvec3.cbegin(); It != vecOfvec3.end(); ++It) {
		vecOfFloats.push_back(It->x);
		vecOfFloats.push_back(It->y);
		vecOfFloats.push_back(It->z);
	}

    return vecOfFloats;
}

void radialize(std::vector<GLfloat> &vertices, GLfloat radius) {
    for (auto It = vertices.begin(); It != vertices.end(); ) {
        auto x = *It; auto y = *(It + 1); auto z = *(It + 2);
        auto norm = static_cast<GLfloat>(sqrt(x * x + y * y + z * z) / radius);
        *It++ = x / norm;
        *It++ = y / norm;
        *It++ = z / norm;
    }
}

void IcoSphere::Refine(unsigned int refinementLevel)
{
	auto verts = convertarrayfromGLFloatTovec3(_vertices);
	std::vector<GLuint> indices = _indices;
	for (auto i = 0u; i < (refinementLevel - _refinementLevel); ++i) {
		decltype(verts) vertsNew;
		decltype(indices) indicesNew;

		for (auto It = indices.cbegin(); It != indices.cend();) {

			// Triangle abc to refine:
			auto aIndex = *It++;
			auto bIndex = *It++;
			auto cIndex = *It++;

			// The coordinates of points a, b and c:
			auto aPoint = verts[aIndex];
			auto bPoint = verts[bIndex];
			auto cPoint = verts[cIndex];

			// For every triangle there are three new points, one in the middle of each side:
			auto abPoint = aPoint + (bPoint - aPoint) / 2.0f;
			auto bcPoint = bPoint + (cPoint - bPoint) / 2.0f;
			auto caPoint = cPoint + (aPoint - cPoint) / 2.0f;

			// Add the new vertices to the new vertice vector:
			auto aIndexNew = static_cast<GLuint>(vertsNew.size());
			vertsNew.push_back(aPoint);
			auto abIndexNew = static_cast<GLuint>(vertsNew.size());
			vertsNew.push_back(abPoint);
			auto bIndexNew = static_cast<GLuint>(vertsNew.size());
			vertsNew.push_back(bPoint);
			auto bcIndexNew = static_cast<GLuint>(vertsNew.size());
			vertsNew.push_back(bcPoint);
			auto cIndexNew = static_cast<GLuint>(vertsNew.size());
			vertsNew.push_back(cPoint);
			auto caIndexNew = static_cast<GLuint>(vertsNew.size());
			vertsNew.push_back(caPoint);

            // Add the four triangles to the new vector of indices:
            // 1
            indicesNew.push_back(caIndexNew);
            indicesNew.push_back(abIndexNew);
            indicesNew.push_back(aIndexNew);
            // 2
            indicesNew.push_back(bcIndexNew);
            indicesNew.push_back(bIndexNew);
            indicesNew.push_back(abIndexNew);
            // 3
            indicesNew.push_back(caIndexNew);
            indicesNew.push_back(cIndexNew);
            indicesNew.push_back(bcIndexNew);
            // 4
            indicesNew.push_back(caIndexNew);
            indicesNew.push_back(bcIndexNew);
            indicesNew.push_back(abIndexNew);
		}
		verts = vertsNew;
		indices = indicesNew;
	}
    if (refinementLevel % 2 == 0) {
        std::reverse(indices.begin(), indices.end());
    }
	_vertices = convertarrayfromVec3ToGLFloat(verts);
	_indices = indices;
	_refinementLevel = refinementLevel;
    radialize(_vertices, _radius);
}

void IcoSphere::GenerateIcosahedron()
{
	GLfloat t = (1.0f + glm::sqrt(5.0f))/2.0f;
	// An icosahedron uses the _vertices of three orthogonal rectangles:

	// Rectangle one:
	_vertices.push_back(-1.0f); _vertices.push_back(t); _vertices.push_back(0);
	_vertices.push_back(1.0f); _vertices.push_back(t); _vertices.push_back(0);
	_vertices.push_back(-1.0f); _vertices.push_back(-t); _vertices.push_back(0);
	_vertices.push_back(1.0f); _vertices.push_back(-t); _vertices.push_back(0);

	// Rectangle two:
	_vertices.push_back(0.f); _vertices.push_back(-1.0f); _vertices.push_back(t);
	_vertices.push_back(0.f); _vertices.push_back(1.f); _vertices.push_back(t);
	_vertices.push_back(0.f); _vertices.push_back(-1.f); _vertices.push_back(-t);
	_vertices.push_back(0.f); _vertices.push_back(1.f); _vertices.push_back(-t);

	// Rectangle three:
	_vertices.push_back(t); _vertices.push_back(0.f); _vertices.push_back(-1.f);
	_vertices.push_back(t); _vertices.push_back(0.f); _vertices.push_back(1.f);
	_vertices.push_back(-t); _vertices.push_back(0.f); _vertices.push_back(-1.f);
	_vertices.push_back(-t); _vertices.push_back(0.f); _vertices.push_back(1.f);

	// Set number vertices:
	_indices.push_back(0); _indices.push_back(11); _indices.push_back(5);
	_indices.push_back(0); _indices.push_back(5); _indices.push_back(1);
	_indices.push_back(0); _indices.push_back(1); _indices.push_back(7);
	_indices.push_back(0); _indices.push_back(7); _indices.push_back(10);
	_indices.push_back(0); _indices.push_back(10); _indices.push_back(11);

	_indices.push_back(1); _indices.push_back(5); _indices.push_back(9);
	_indices.push_back(5); _indices.push_back(11); _indices.push_back(4);
	_indices.push_back(11); _indices.push_back(10); _indices.push_back(2);
	_indices.push_back(10); _indices.push_back(7); _indices.push_back(6);
	_indices.push_back(7); _indices.push_back(1); _indices.push_back(8);

	_indices.push_back(3); _indices.push_back(9); _indices.push_back(4);
	_indices.push_back(3); _indices.push_back(4); _indices.push_back(2);
	_indices.push_back(3); _indices.push_back(2); _indices.push_back(6);
	_indices.push_back(3); _indices.push_back(6); _indices.push_back(8);
	_indices.push_back(3); _indices.push_back(8); _indices.push_back(9);

	_indices.push_back(4); _indices.push_back(9); _indices.push_back(5);
	_indices.push_back(2); _indices.push_back(4); _indices.push_back(11);
	_indices.push_back(6); _indices.push_back(2); _indices.push_back(10);
	_indices.push_back(8); _indices.push_back(6); _indices.push_back(7);
	_indices.push_back(9); _indices.push_back(8); _indices.push_back(1);
}



