#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QElapsedTimer>
#include <QTimer>
#include <QWindow>
#include <memory>

#include "glm/glm.hpp"
#include "qtopenglproxy.hpp"
#include "renderer.h"
#include "scene.h"
#include "world.h"

class OpenGLWindow : public QWindow {
  Q_OBJECT
 public:
  explicit OpenGLWindow(QWindow *parent = nullptr);
  OpenGLWindow(QWindow *parent, QSurfaceFormat f);
  ~OpenGLWindow() override;

  void initialize();

  void setRenderer(Renderer *renderer);
  void setScene(Scene *scene);
  void setFunctions(std::shared_ptr<OpenGLFunctionProxy> openglProxy);

  OpenGLFunctionProxy *createFunctionProxy();
  Shader *createShader(const std::string &vertexPath,
                       const std::string &fragmentPath);
  void initializeTimer();

 public slots:
  void update();
  void render();

 private:
  long long _lastNanos;
  QPoint _center;

  std::unique_ptr<QTimer> _updateTimer, _renderTimer;
  std::unique_ptr<QElapsedTimer> _elapsedTimer;
  std::unique_ptr<QOpenGLContext> openglContext;
  std::unique_ptr<Renderer> _renderer;
  std::unique_ptr<Scene> _scene;
  std::shared_ptr<OpenGLFunctionProxy> openglProxy;

  // QWindow interface
 protected:
  void resizeEvent(QResizeEvent *) override;
  void keyPressEvent(QKeyEvent *) override;
  void keyReleaseEvent(QKeyEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;
};

#endif  // OPENGLWIDGET_H
