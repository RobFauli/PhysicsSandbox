#ifndef PHYSICSSANDBOX_LIGHTSOURCE_HPP
#define PHYSICSSANDBOX_LIGHTSOURCE_HPP

#include <glm/vec3.hpp>

class LightSource
{
public:
    LightSource(glm::vec3 position) : _position(position) { };

    const auto &getPosition() {
        return _position;
    }

private:
    glm::vec3 _position;
};


#endif //PHYSICSSANDBOX_LIGHTSOURCE_HPP
