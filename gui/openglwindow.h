#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <memory>
#include <QWindow>
#include <QTimer>
#include <QElapsedTimer>

#include "glm/glm.hpp"
#include "qtopenglproxy.hpp"
#include "world.hpp"
#include "renderer.h"

class OpenGLWindow : public QWindow
{
  Q_OBJECT
public:
  explicit OpenGLWindow(QWindow *parent = nullptr);
  OpenGLWindow(QWindow *parent, QSurfaceFormat f);
  ~OpenGLWindow();

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
  std::shared_ptr<OpenGLFunctionProxy> functions;
  std::unique_ptr<QOpenGLContext> openglContext;
  std::unique_ptr<Renderer> renderer;
  std::unique_ptr<World<RenderableEntity>> world;

  void initializeFunctionProxy();
  void initializeShader();
  void initializeTimer();

  // QWindow interface
protected:
  void resizeEvent(QResizeEvent *) override;
  void keyPressEvent(QKeyEvent *) override;
  void keyReleaseEvent(QKeyEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;
};

#endif // OPENGLWIDGET_H
