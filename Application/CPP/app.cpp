#include "app.hpp"

int app(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
  

#ifndef NO_QRC
    Q_INIT_RESOURCE(app);
    
    QuickView view(QUrl(QStringLiteral("qrc:/main.qml")));
#else
    QuickView view(QUrl(QSTRINGLIST_H("../Application/QML/main.qml")));
#endif
    view.show();

    return app.exec();
}
