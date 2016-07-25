//
// Created by robertfa on 14.06.16.
//

#include "Cube.hpp"

Cube::Cube(const std::shared_ptr<Shader> shader, GLfloat length, GLfloat width, GLfloat height) {

    // The length, width and height is measured along the x, y and z-axis respectively.
    GLfloat xa = -length / 2.0f;
    GLfloat xb = length / 2.0f;
    GLfloat ya = -width / 2.0f;
    GLfloat yb = width / 2.0f;
    GLfloat za = -height / 2.0f;
    GLfloat zb = height / 2.0f;

    // A cube has 8 corners.
    _vertices = std::vector<GLfloat>{ // We put the coordinates of one corner on each line.
            xa, ya, za,
            xa, ya, zb,
            xa, yb, za,
            xa, yb, zb,
            xb, ya, za,
            xb, ya, zb,
            xb, yb, za,
            xb, yb, zb
    };

    // Each of the six sides is drawn as two triangles
    // The indices of each triangle should to counterclockwise seen from outside the cube
    _indices = std::vector<GLuint>{ // We put the indices of a triangle in each line.
        0, 2, 1, // xa (xa, ya, za) -> (xa, yb, za) -> (xa, ya, zb)
        3, 1, 2, //    (xa, yb, zb) -> (xa, ya, zb) -> (xa, yb, za)
        4, 5, 6, // xb (xb, ya, za) -> (xb, ya, zb) -> (xb, yb, za)
        7, 6, 5, //    (xb, yb, zb) -> (xb, yb, za) -> (xb, ya, zb)
        0, 1, 4, // ya
        5, 4, 1,
        6, 3, 2, // yb
        3, 6, 7,
        4, 2, 0, // za
        2, 4, 6,
        1, 3, 5, // zb
        7, 5, 3
    };
}

