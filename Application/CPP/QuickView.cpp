#include "QuickView.hpp"

QuickView::QuickView(QWindow *parent)
    : QQuickView(parent),
      _camera(Camera()),
      _renderer(std::make_shared<Renderer>(Renderer()))
{
    connect(this, &QQuickWindow::sceneGraphInitialized,
            this, &QuickView::initializeUnderlay,
            Qt::DirectConnection);

    connect(this, &QQuickWindow::beforeSynchronizing,
            this, &QuickView::synchronizeUnderlay,
            Qt::DirectConnection);

    connect(this, &QQuickWindow::beforeRendering,
            this, &QuickView::renderUnderlay,
            Qt::DirectConnection);

    connect(this, &QQuickWindow::sceneGraphInvalidated,
            this, &QuickView::invalidateUnderlay,
            Qt::DirectConnection);

    setClearBeforeRendering(false);
    setPersistentOpenGLContext(true);

    setResizeMode(SizeRootObjectToView);
    _mngr.registerEnumsQML();
    rootContext()->setContextProperty("mngr", &_mngr);
    setSource(QUrl("qrc:/main.qml"));
}
void QuickView::synchronizeUnderlay()
{
    _renderer->setFOV(_camera.Zoom);
    _renderer->setView(_camera.GetViewMatrix());
    _renderer->setHeigh(height());
    _renderer->setWidth(width());
    _mngr.updateObjects();
}
void QuickView::initializeUnderlay()
{
    QSurfaceFormat format;
    format.setMajorVersion(3);
    format.setMinorVersion(3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    setFormat(format);

    _renderer->initialize();
    _mngr.setRenderer(_renderer);
}
void QuickView::renderUnderlay()
{
    _renderer->draw();
}
