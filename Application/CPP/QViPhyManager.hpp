#ifndef PHYSICSSANDBOX_VIPHYMANAGER_HPP
#define PHYSICSSANDBOX_VIPHYMANAGER_HPP

#include <QtCore/QObject>
#include <QtCore/QVariantMap>

#include <Simulation.hpp>
#include <Window.hpp>
#include "Object.hpp"

enum ForceEnum { GRAVITY, COLOUMB };
enum TimeUnitEnum { SECONDS, YEARS };
enum LengthUnitEnum { NANO_METERS, CENTI_METERS, METERS, KILO_METERS, LIGHT_YEARS };

enum ODESolverEnum { EULER, LEAPFROG };

//! This class manages and runs simulations and visualizations,
//! whether simulated while visualizing or before.

class QViPhyManager : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE void startSimulating();
    Q_INVOKABLE void startRendering();
    Q_INVOKABLE void startLiveRendering();

    Q_INVOKABLE QList<QString> getObjectNames();
    Q_INVOKABLE QVariantMap getObjectMasses();
    Q_INVOKABLE QVariantMap getObjectCharges();

    Q_INVOKABLE void addObject(QString keyname,
                               qreal mass, qreal charge,
                               qreal x, qreal y, qreal z);
    Q_INVOKABLE void removeObject(QString keyname);

    Q_INVOKABLE void addForce(ForceEnum force);
    Q_INVOKABLE void removeForce(ForceEnum force);

    Q_INVOKABLE void changeTimeUnitsTo(TimeUnitEnum timeUnit);
    Q_INVOKABLE void changeLengthUnitsTo(LengthUnitEnum lengthUnit);

private:
    void setupSimulation();
    void setupWindow();

    std::unique_ptr<Simulation> _simulation = std::make_unique<Simulation>(Simulation());
    std::unique_ptr<Window> _window = nullptr;
    QMap<QString, std::unique_ptr<Object>> _objects;

    // Settings variables
    bool _preSimulated;
    unsigned int _windowHeight;
    unsigned int _windowWidth;

    ODESolverEnum _odeSolverEnum = LEAPFROG;
};


#endif //PHYSICSSANDBOX_VIPHYMANAGER_HPP
