#ifndef PHYSICSSANDBOX_CUBE_HPP
#define PHYSICSSANDBOX_CUBE_HPP


#include "Triangles.hpp"

class Cube : public Triangles {
public:
    Cube(const Shader &shader, GLfloat length, GLfloat breadth, GLfloat height);

};


#endif //PHYSICSSANDBOX_CUBE_HPP
