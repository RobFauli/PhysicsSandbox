#ifndef PHYSICSSANDBOX_TRANSFORMATIONMATRICES_HPP
#define PHYSICSSANDBOX_TRANSFORMATIONMATRICES_HPP

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

inline auto genModelMatrix(const glm::vec3 &position,
                           const glm::vec3 &rotateAlong = glm::vec3(0, 0, 0),
                           const GLfloat radiansRotated = 0)
{
    glm::mat4 model;
    model = glm::translate(model, position);

    if (rotateAlong != glm::vec3(0, 0, 0))
        model = glm::rotate(model, radiansRotated, rotateAlong);
    else
    {}

    return model;
}

#endif //PHYSICSSANDBOX_TRANSFORMATIONMATRICES_HPP
