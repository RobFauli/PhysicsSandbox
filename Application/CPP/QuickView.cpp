#include "QuickView.hpp"

QuickView::QuickView(QWindow *parent)
    : QQuickView(parent),
      _camera(Camera())
{
    //QSurfaceFormat format;
    /*
    format.setMajorVersion(4);
    format.setMinorVersion(2);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setSamples(4);
    setFormat(format);
    */
    //format.setDefaultFormat(format);
    //setFormat(format);

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
    _mngr.loadRenderer();
    resetOpenGLState();
}
void QuickView::initializeUnderlay()
{
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW." << std::endl;
        exit(-1);
    }
    glEnable(GL_DEPTH_TEST);
    _renderer = std::make_shared<Renderer>(Renderer(glm::vec4(0, 0, 0, 1)));
    _renderer->setFOV(_camera.Zoom);
    _renderer->setView(_camera.GetViewMatrix());
    _renderer->setHeigh(height());
    _renderer->setWidth(width());
    auto ls = std::make_shared<LightSource>(LightSource(glm::vec3(20, 0, 6)));
    _renderer->addLightSource(ls);
    _mngr.setRenderer(_renderer);
    resetOpenGLState();
}
void QuickView::renderUnderlay()
{
    _renderer->draw();
    resetOpenGLState();
}
