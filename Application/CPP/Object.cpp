#include <Shapes/IcoSphere.hpp>
#include "Object.hpp"

Object::Object(std::shared_ptr<Shader> shader, double mass, double charge,
               float length, float width, float height)
: _physicalProperties(std::make_shared<PointParticle>(PointParticle(mass, charge))),
  _shape(std::make_shared<Cube>(shader, length, width, height))
{

}
Object::Object(std::shared_ptr<Shader> shader, double mass, double charge, float radius)
    : _physicalProperties(std::make_shared<PointParticle>(PointParticle(mass, charge))),
      _shape(std::make_shared<IcoSphere>(shader, 3u, radius)) // TODO Set refinement levels elsewhere.
{

}



