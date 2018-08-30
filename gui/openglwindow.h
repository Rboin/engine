#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <memory>
#include <QWindow>
#include <QTimer>
#include <QElapsedTimer>

#include "glm/glm.hpp"
#include "qtopenglproxy.hpp"
#include "world.h"
#include "renderer.h"

class OpenGLWindow : public QWindow
{
  Q_OBJECT
public:
  explicit OpenGLWindow(QWindow *parent = nullptr);
  OpenGLWindow(QWindow *parent, QSurfaceFormat f);
  ~OpenGLWindow();

  void initialize();

  void setWorld(World *world);
  void setCamera(std::shared_ptr<Camera> camera);

  std::shared_ptr<OpenGLFunctionProxy> createFunctionProxy();
  Shader *createShader();
  void initializeTimer();

public slots:
  void update();
private:
  long long _lastNanos;
  QPoint _center;

  std::unique_ptr<QTimer> _updateTimer, _renderTimer;
  std::unique_ptr<QElapsedTimer> _elapsedTimer;
  std::shared_ptr<OpenGLFunctionProxy> functions;
  std::unique_ptr<QOpenGLContext> openglContext;
  std::shared_ptr<Camera> camera;
  std::unique_ptr<World> world;

  // QWindow interface
protected:
  void resizeEvent(QResizeEvent *) override;
  void keyPressEvent(QKeyEvent *) override;
  void keyReleaseEvent(QKeyEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;
};

#endif // OPENGLWIDGET_H
