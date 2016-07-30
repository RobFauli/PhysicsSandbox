#ifndef PHYSICSSANDBOX_APP_HPP
#define PHYSICSSANDBOX_APP_HPP

#include "CPP/QuickView.hpp"
#include <QtGui/QGuiApplication>

auto app(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Q_INIT_RESOURCE(app);

    QuickView view;
    view.show();

    return app.exec();
}

#endif //PHYSICSSANDBOX_APP_HPP
