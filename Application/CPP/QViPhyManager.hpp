#ifndef PHYSICSSANDBOX_VIPHYMANAGER_HPP
#define PHYSICSSANDBOX_VIPHYMANAGER_HPP

#include <QtCore/QObject>
#include <QtCore/QVariantMap>

#include <zconf.h>

#include <Simulation.hpp>
#include <Window.hpp>
#include <EquationSolvers/DifferentialEquations/Ordinary/Leapfrog.hpp>
#include <QtQml/QtQml>
#include "Object.hpp"




//! This class manages and runs simulations and visualizations,
//! whether simulated while visualizing or before.

class QViPhyManager : public QObject
{
    Q_OBJECT

public:
    enum class ForceEnum { GRAVITY, COULOMB };
    enum class TimeUnitEnum { SECONDS, YEARS };
    enum class LengthUnitEnum { NANO_METERS, CENTI_METERS, METERS, KILO_METERS, LIGHT_YEARS };
    enum class ODESolverEnum { EULER, LEAPFROG };

    Q_ENUM(ForceEnum)
    Q_ENUM(TimeUnitEnum)
    Q_ENUM(LengthUnitEnum)
    Q_ENUM(ODESolverEnum)

    //QViPhyManager() { }
    static void registerEnumsQML() {
        qmlRegisterType<QViPhyManager>("Enums", 1, 0, "ForceEnum");
    }

    Q_INVOKABLE void startSimulating();
    Q_INVOKABLE void startRendering();
    Q_INVOKABLE void startLiveRendering(QString monitorName = NULL);

    Q_INVOKABLE QList<QString> getObjectNames();
    Q_INVOKABLE QVariantMap getObjectMasses();
    Q_INVOKABLE QVariantMap getObjectCharges();

    Q_INVOKABLE void addObject(QString keyname,
                                   qreal mass, qreal charge, qreal radius,
                                   qreal x, qreal y, qreal z);
    Q_INVOKABLE void removeObject(QString keyname);

    Q_INVOKABLE void setObjectVelocity(QString keyname, qreal vx, qreal vy, qreal vz);

    Q_INVOKABLE void addForce(ForceEnum force);
    Q_INVOKABLE void removeForce(ForceEnum force);

    Q_INVOKABLE void changeTimeUnitsTo(TimeUnitEnum timeUnit);
    Q_INVOKABLE void changeLengthUnitsTo(LengthUnitEnum lengthUnit);

    Q_INVOKABLE void setLightPosition(qreal x, qreal y, qreal z)
    {
        if (!_light)
            _light = true;
        _lightPos = glm::vec3(x, y, z);
    }

private:
    void setupSimulation();
    void setupWindow();

    bool _light = false;
    glm::vec3 _lightPos;

    std::unique_ptr<Simulation> _simulation = std::make_unique<Simulation>(Simulation());
    Window _window;
    QMap<QString, Object> _objects;

    // Settings variables
    bool _preSimulated;
    unsigned int _windowHeight = 600;
    unsigned int _windowWidth = 800;
    std::string _windowTitle = "Default title";
    glm::vec4 _backgroundColor = glm::vec4(0.f, 0.f, 0.f, 1.f);
    qreal _sleep = 1e1;

    ODESolverEnum _odeSolverEnum = ODESolverEnum::LEAPFROG;

    std::string _vertexPath = "../../Visualization/Shaders/VertexShader.glsl";
    std::string _geometryPath = "../../Visualization/Shaders/GeometryShader.glsl";
    std::string _fragmentPath = "../../Visualization/Shaders/FragmentShader.glsl";
    std::shared_ptr<Shader> _shader;
    void loadRenderer();
    void loadSimulation() const;
};


#endif //PHYSICSSANDBOX_VIPHYMANAGER_HPP
