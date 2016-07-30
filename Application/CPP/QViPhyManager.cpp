#include "QViPhyManager.hpp"

void QViPhyManager::startSimulating()
{
    setupSimulation();
}
void QViPhyManager::startRendering()
{
}
void QViPhyManager::startLiveRendering()
{
    _simulation->runNSteps(10);
        for (auto &object : _objects) {
            object.updateShapePosition();
    }
}
QList<QString> QViPhyManager::getObjectNames()
{
    return _objects.keys();
}
QVariantMap QViPhyManager::getObjectMasses()
{
    QVariantMap masses;

    for (auto It = _objects.cbegin(); It != _objects.cend(); ++It) {
        masses.insert(It.key(), QVariant(It.value().getMass()));
    }

    return masses;
}
QVariantMap QViPhyManager::getObjectCharges()
{
    QVariantMap charges;
    for (auto It = _objects.cbegin(); It != _objects.cend(); ++It) {
        charges.insert(It.key(), QVariant(It.value().getCharge()));
    }
    return charges;
}
void QViPhyManager::addObject(QString keyname,
                              qreal mass, qreal charge, qreal radius,
                              qreal x, qreal y, qreal z)
{
    _objects.insert(
        keyname,
        Object(
            _shader, mass, charge, radius)
    );
    _objects.find(keyname).value().setPosition(x, y, z);
    _objects.find(keyname).value().setColor(1.0f, 0.0f, 0.0f);
}
void QViPhyManager::removeObject(QString keyname)
{
    _objects.remove(keyname);
}
void QViPhyManager::addForce(ForceEnum forceEnum)
{
    std::shared_ptr<Force> force;
    switch(forceEnum) {
        case ForceEnum::GRAVITY: {
            auto GForce = std::make_shared<GravitationalForce>(GravitationalForce());
            GForce->setSoftener(0.05 * 0.05);
            force = GForce;
            _simulation->addForce(force);
            break;
        }
        case ForceEnum::COULOMB: {
            auto CForce = std::make_shared<ColoumbForce>(ColoumbForce());
            CForce->setSoftener(0.05 * 0.05);
            force = CForce;
            _simulation->addForce(force);
            break;
        }
    }
}
void QViPhyManager::removeForce(ForceEnum force)
{

}
void QViPhyManager::changeTimeUnitsTo(TimeUnitEnum timeUnit)
{
    // Shouldn't this switch be inn the PhysicalConstants class?
    switch (timeUnit) {
        case TimeUnitEnum::SECONDS:
            _simulation->changeTimeUnitsTo("s");
            break;
        case TimeUnitEnum::YEARS:
            _simulation->changeTimeUnitsTo("yr");
            break;
    }
}
void QViPhyManager::changeLengthUnitsTo(LengthUnitEnum lengthUnit)
{
    // Shouldn't this switch be inn the PhysicalConstants class?
    switch (lengthUnit) {
        case LengthUnitEnum::NANO_METERS:
            _simulation->changeTimeUnitsTo("ns");
            break;
        case LengthUnitEnum::CENTI_METERS:
            _simulation->changeTimeUnitsTo("cm");
            break;
        case LengthUnitEnum::METERS:
            _simulation->changeTimeUnitsTo("m");
            break;
        case LengthUnitEnum::KILO_METERS:
            _simulation->changeTimeUnitsTo("km");
            break;
        case LengthUnitEnum::LIGHT_YEARS:
            _simulation->changeTimeUnitsTo("ly");
            break;
    }
}
void QViPhyManager::setupSimulation()
{
    switch (_odeSolverEnum) {
        case ODESolverEnum::LEAPFROG:
            _simulation->changeODESolver(std::make_unique<Leapfrog>(Leapfrog()));
            break;
        case ODESolverEnum::EULER:
            _simulation->changeODESolver(std::make_unique<Euler>(Euler()));
    }

    loadSimulation();
}
void QViPhyManager::loadSimulation() const
{
    _simulation->removeAllBodies();
    for (const auto &object : _objects) {
        _simulation->addBody(object.getBody());
    }
}
void QViPhyManager::loadRenderer()
{
    _renderer->removeAllObjects();
    for (auto &object : _objects) {
        _renderer->addObject(object.getShape());
    }
}
void QViPhyManager::setObjectVelocity(QString keyname, qreal vx, qreal vy, qreal vz)
{
    _objects.find(keyname)->setVelocity(vx, vy, vz);
}

