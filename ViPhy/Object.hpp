#ifndef PHYSICSSANDBOX_OBJECT_HPP
#define PHYSICSSANDBOX_OBJECT_HPP

#include <Bodies/PointParticleCreator.hpp>
#include <Shapes/Cube.hpp>
#include <Bodies/Body.hpp>
#include <Shapes/Shape.hpp>
class Object
{
public:
    Object(const Shader &shader,
           double mass, double charge,
           float length, float width, float height); // Cube
    Object(const Shader &shader,
           double mass, double charge,
           float radius); // Sphere
    Object(std::unique_ptr<Body> pp, std::unique_ptr<Shape> shape)
        : _physicalProperties(std::move(pp)), _shape(std::move(shape)) { }

    void changeShape(std::unique_ptr<Shape> shape)
    {
        _shape = std::move(shape);
    }
    void changePhysicalProperties(std::unique_ptr<Body> pp)
    {
        //_physicalProperties = std::move(pp);
    }
    void setPosition(double x, double y, double z) {
        //_physicalProperties->setPosition(x, y, z);
        //_shape->setPosition(x, y, z, 0);
    }
    void move(double dx, double dy, double dz) {
        //_physicalProperties->move(dx, dy, dz);
        //_shape->move(dx, dy, dz);
    }
    void rotate(double radians, double pivotX, double pivotY, double pivotZ) {
        //_physicalProperties->rotate(radians, pivotX, pivotY, pivotZ);
        //_shape->rotate(radians, pivotX, pivotY, pivotZ);
    }
private:
    std::unique_ptr<Body> _physicalProperties;
    std::unique_ptr<Shape> _shape;
};


#endif //PHYSICSSANDBOX_OBJECT_HPP
