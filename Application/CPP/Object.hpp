#ifndef PHYSICSSANDBOX_OBJECT_HPP
#define PHYSICSSANDBOX_OBJECT_HPP

#include <Bodies/PointParticleCreator.hpp>
#include <Shapes/Cube.hpp>
#include <Bodies/Body.hpp>
#include <Shapes/Shape.hpp>
class Object
{
public:
    Object(std::shared_ptr<Shader> shader,
           double mass, double charge,
           float length, float width, float height); // Cube
    Object(std::shared_ptr<Shader> shader,
           double mass, double charge,
           float radius); // Sphere
    Object(std::shared_ptr<Body> pp, std::shared_ptr<Shape> shape)
        : _physicalProperties(pp), _shape(shape) { }

    void changeShape(std::shared_ptr<Shape> shape)
    {
        _shape = shape;
    }
    void changePhysicalProperties(std::shared_ptr<Body> pp)
    {
        _physicalProperties = pp;
    }
    void setPosition(double x, double y, double z) {
        _physicalProperties->setPosition(x, y, z);
        _shape->setPosition(x, y, z);
    }
    void setVelocity(double vx, double vy, double vz) {
        _physicalProperties->setVelocity(Vector3<double>(vx, vy, vz));
    }
    void move(double dx, double dy, double dz) {
        _physicalProperties->move(dx, dy, dz);
        _shape->move(dx, dy, dz);
    }

    // TODO Need to implement rotations on the physical end as soon as we have rotatable objects.
    void rotate(double radians, double pivotX, double pivotY, double pivotZ) {
        //_physicalProperties->rotate(radians, pivotX, pivotY, pivotZ);
        _shape->rotate(radians, pivotX, pivotY, pivotZ);
    }

    auto getMass() const {
        return _physicalProperties->getMass();
    }
    auto getCharge() const
    {
        return _physicalProperties->getCharge();
    }
    auto getPosition() const {
        return _physicalProperties->getPosition();
    }
    auto getVelocity() const {
        return _physicalProperties->getVelocity();
    }

    std::shared_ptr<Body> const &getBody() const {
        return _physicalProperties;
    }
    std::shared_ptr<Shape> const &getShape() const {
        return _shape;
    }

    void updateShapePosition() {
        auto pos = _physicalProperties->getPosition();
        _shape->setPosition(static_cast<GLfloat>(pos.x), static_cast<GLfloat>(pos.y),
                            static_cast<GLfloat>(pos.z));
    }

    void setColor(GLfloat r, GLfloat g, GLfloat b) {
        _shape->setColor(r, g, b);
    }
    auto getColor() {
        return _shape->getColor();
    }

private:
    std::shared_ptr<Body> _physicalProperties;
    std::shared_ptr<Shape> _shape;
};


#endif //PHYSICSSANDBOX_OBJECT_HPP
