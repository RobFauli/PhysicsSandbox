#ifndef PHYSICSSANDBOX_APP_HPP
#define PHYSICSSANDBOX_APP_HPP

#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QQmlContext>
#include "CPP/QViPhyManager.hpp"

auto app(int argc, char *argv[])
{
    QViPhyManager mngr;

    Q_INIT_RESOURCE(app);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    mngr.registerEnumsQML();
    engine.load(QUrl("qrc:/main.qml"));
    engine.rootContext()->setContextProperty("mngr", &mngr);
    return app.exec();
}

#endif //PHYSICSSANDBOX_APP_HPP
