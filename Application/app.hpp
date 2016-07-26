#ifndef PHYSICSSANDBOX_APP_HPP
#define PHYSICSSANDBOX_APP_HPP

#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>

auto app(int argc, char *argv[])
{
    Q_INIT_RESOURCE(app);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load(QUrl("qrc:/main.qml"));

    return app.exec();
}

#endif //PHYSICSSANDBOX_APP_HPP
