#ifndef PHYSICSSANDBOX_LIGHTSOURCE_HPP
#define PHYSICSSANDBOX_LIGHTSOURCE_HPP

#include <glm/vec3.hpp>

class LightSource
{
public:
    LightSource(const glm::vec3 &position) : _position(position) { };

    const auto &getPosition() {
        return _position;
    }

    const auto &getLightColor() {
        return _lightColor;
    }

    void setPosition(const glm::vec3 &position) {
        _position = position;
    }

    void setLightColor(const glm::vec3 &color) {
        _lightColor = color;
    }

private:
    glm::vec3 _position;
    glm::vec3 _lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
};


#endif //PHYSICSSANDBOX_LIGHTSOURCE_HPP
