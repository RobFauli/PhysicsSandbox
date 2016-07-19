#include <Shapes/IcoSphere.hpp>
#include "Object.hpp"

Object::Object(const Shader &shader, double mass, double charge,
               float length, float width, float height)
: _physicalProperties(std::make_unique<PointParticle>(PointParticle(mass, charge))),
  _shape(std::make_unique<Cube>(Cube(shader, length, width, height)))
{

}
Object::Object(const Shader &shader, double mass, double charge, float radius)
    : _physicalProperties(std::make_unique<PointParticle>(PointParticle(mass, charge))),
      _shape(std::make_unique<IcoSphere>(IcoSphere(shader, 4u, radius)))
{

}



