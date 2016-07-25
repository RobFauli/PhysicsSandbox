#ifndef PHYSICSSANDBOX_CUBE_HPP
#define PHYSICSSANDBOX_CUBE_HPP


#include <memory>
#include "Triangles.hpp"

class Cube : public Triangles {
public:
    Cube(const std::shared_ptr<Shader> shader, GLfloat length, GLfloat width, GLfloat height);

};


#endif //PHYSICSSANDBOX_CUBE_HPP
