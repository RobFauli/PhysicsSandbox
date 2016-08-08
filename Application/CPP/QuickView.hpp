#ifndef PHYSICSSANDBOX_QUICKVIEW_HPP
#define PHYSICSSANDBOX_QUICKVIEW_HPP


#include <Camera.hpp>
#include <Renderer.hpp>
#include <QQuickView>
#include <QOpenGLContext>
#include "QViPhyManager.hpp"

class QuickView : public QQuickView
{
    Q_OBJECT

public:
    QuickView(QWindow *parent = 0);

public slots:
    void initializeUnderlay();
    void synchronizeUnderlay();
    void renderUnderlay();
    void invalidateUnderlay() {};

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    Camera _camera;
    std::shared_ptr<Renderer> _renderer;
    QViPhyManager _mngr;
};


#endif //PHYSICSSANDBOX_QUICKVIEW_HPP
