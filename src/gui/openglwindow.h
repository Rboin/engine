#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <memory>
#include <QWindow>
#include <QTimer>
#include <QElapsedTimer>
#include "glm/glm.hpp"
#include "qtopenglproxy.h"
#include "world.hpp"
#include "entities/renderableentity.h"
#include "renderer/renderer.h"

class OpenGLWindow : public QWindow
{
  Q_OBJECT
public:
  OpenGLWindow(QSurfaceFormat f, QWindow *parent = nullptr);
  virtual ~OpenGLWindow() Q_DECL_OVERRIDE;

  void initialize();

  void setWorld(World<RenderableEntity> *world);
  void setRenderer(Renderer *renderer);

public slots:
  void update();
  void render();
private:
  long long _lastNanos;
  QPoint _center;

  std::unique_ptr<QTimer> _updateTimer, _renderTimer;
  std::unique_ptr<QElapsedTimer> _elapsedTimer;
  std::unique_ptr<Renderer> renderer;
  std::unique_ptr<World<RenderableEntity>> world;
  std::unique_ptr<QOpenGLContext> openglContext;
  std::shared_ptr<OpenGLFunctionProxy> functions;

  void initializeFunctionProxy();
  void initializeShader();
  void initializeTimer();

  // QWindow interface
protected:
  void resizeEvent(QResizeEvent *) override;
  void keyPressEvent(QKeyEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;
};

#endif // OPENGLWIDGET_H
