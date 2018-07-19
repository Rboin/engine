#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <memory>
#include <QOpenGLWindow>
#include <QTimer>
#include "glm/glm.hpp"
#include "qtopenglproxy.h"
#include "world.hpp"
#include "entities/renderableentity.h"
#include "renderer/renderer.h"

class OpenGLWindow : public QOpenGLWindow
{
  Q_OBJECT
public:
  OpenGLWindow(QSurfaceFormat f);
  virtual ~OpenGLWindow() Q_DECL_OVERRIDE;

  void setWorld(World<RenderableEntity> *world);
  void setRenderer(Renderer *renderer);

  // QOpenGLWindow interface
protected:
  void initializeGL() Q_DECL_OVERRIDE;
  void resizeGL(int w, int h) Q_DECL_OVERRIDE;
  void paintGL() Q_DECL_OVERRIDE;
private:
  bool running;
  glm::mat4 projection;
  QSurfaceFormat format;
  std::unique_ptr<QTimer> timer;
  std::unique_ptr<Renderer> renderer;
  std::unique_ptr<World<RenderableEntity>> world;
//  std::unique_ptr<QOpenGLContext> openglContext;
  std::shared_ptr<OpenGLFunctionProxy> functions;

  void initializeFunctionProxy();
  void initializeShader();

  // QObject interface
public:
//  bool event(QEvent *event) Q_DECL_OVERRIDE;
};

#endif // OPENGLWIDGET_H
