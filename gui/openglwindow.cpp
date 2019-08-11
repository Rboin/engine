#include "openglwindow.h"

#include <GL/gl.h>
#include <QFile>
#include <QOpenGLExtraFunctions>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_3_Core>
#include <QResizeEvent>
#include <QtDebug>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"
#include "shaderinformation.h"

OpenGLWindow::OpenGLWindow(QWindow *parent, QSurfaceFormat f)
    : OpenGLWindow(parent) {
  this->setSurfaceType(QWindow::OpenGLSurface);
  this->setFormat(f);
  this->create();
  this->setCursor(Qt::BlankCursor);
  this->_lastNanos = 0;
}

OpenGLWindow::OpenGLWindow(QWindow *parent) : QWindow(parent) {}

OpenGLWindow::~OpenGLWindow() {
  if (this->openglContext) {
    this->openglContext->makeCurrent(this);
  }
}

void OpenGLWindow::initialize() {
  //  this->createFunctionProxy();
  //  this->createShader();
  this->initializeTimer();
}

void OpenGLWindow::setRenderer(Renderer *renderer) {
  this->_renderer = std::unique_ptr<Renderer>(renderer);
}

void OpenGLWindow::setScene(Scene *scene) {
  this->_scene = std::unique_ptr<Scene>(scene);
}

void OpenGLWindow::setFunctions(
    std::shared_ptr<OpenGLFunctionProxy> openglProxy) {
  this->openglProxy = openglProxy;
}

void OpenGLWindow::update() {
  long long elapsed = this->_elapsedTimer->nsecsElapsed();
  double deltaSeconds =
      static_cast<double>(elapsed - this->_lastNanos) / 1000000000;

  //  qDebug() << "Updating with delta: " << deltaSeconds;
  this->_scene->update(deltaSeconds);
  this->_lastNanos = elapsed;
}

void OpenGLWindow::render() {
  if (this->_renderer && this->_scene && this->isExposed()) {
    this->openglContext->makeCurrent(this);
    this->_renderer->render(this->_scene);
    this->openglContext->swapBuffers(this);
  }
}

OpenGLFunctionProxy *OpenGLWindow::createFunctionProxy() {
  OpenGLFunctionProxy *openglProxy;
  // Get current OpenGL context.
  this->openglContext = std::make_unique<QOpenGLContext>(this);
  this->openglContext->setFormat(this->requestedFormat());
  bool created = this->openglContext->create();
  if (created) {
    this->openglContext->makeCurrent(this);
    QOpenGLExtraFunctions *f = this->openglContext->extraFunctions();
    if (!f) {
      qWarning() << "Could not get the version functions...";
    }
    f->initializeOpenGLFunctions();
    openglProxy = new QtOpenGLProxy<QOpenGLExtraFunctions>(f);
    // TODO: till this...
    const char *glVersion = (const char *)openglProxy->glGetString(GL_VERSION),
               *glslVersion = (const char *)openglProxy->glGetString(
                   GL_SHADING_LANGUAGE_VERSION);
    qDebug() << "Initialized OpenGL with version:" << glVersion
             << "GLSL:" << glslVersion;
  }
  return openglProxy;
}

Shader *OpenGLWindow::createShader(const std::string &vertexPath,
                                   const std::string &fragmentPath) {
  QFile vertexfile(vertexPath.c_str()), fragmentFile(fragmentPath.c_str());
  bool open = vertexfile.open(QFile::ReadOnly | QFile::Text) &&
              fragmentFile.open(QFile::ReadOnly | QFile::Text);
  if (!open) {
    qDebug() << "Could not open shader files...";
  }
  QTextStream vertexStream(&vertexfile), fragmentStream(&fragmentFile);
  QString vertexSource = vertexStream.readAll(),
          fragmentSource = fragmentStream.readAll();
  vertexStream.flush();
  fragmentStream.flush();
  vertexfile.close();
  fragmentFile.close();
  ShaderInformation *shaderInformation = new ShaderInformation(
      vertexSource.toStdString(), fragmentSource.toStdString());
  Shader *shader = new Shader(shaderInformation);
  //  this->_renderer->addShader(shader);
  return shader;
}

void OpenGLWindow::initializeTimer() {
  this->_renderTimer = std::make_unique<QTimer>(this);
  this->_updateTimer = std::make_unique<QTimer>(this);
  this->_elapsedTimer = std::make_unique<QElapsedTimer>();

  this->connect(this->_updateTimer.get(), SIGNAL(timeout()), this,
                SLOT(update()));
  this->connect(this->_renderTimer.get(), SIGNAL(timeout()), this,
                SLOT(render()));

  this->_updateTimer->start();
  this->_renderTimer->start();
  this->_elapsedTimer->start();
}

void OpenGLWindow::resizeEvent(QResizeEvent *e) {
  int width = e->size().width(), height = e->size().height();
  this->_renderer->getFunctionProxy()->glViewport(0, 0, width, height);
  this->_scene->getCamera().updateViewMatrix();
  this->_scene->getCamera().updateProjectionMatrix(width, height);
  QSize currentSize = this->size();
  this->_center = QPoint(currentSize.width() / 2, currentSize.height() / 2);
}

void OpenGLWindow::keyPressEvent(QKeyEvent *e) {
  switch (e->key()) {
    case Qt::Key_W:
      this->_scene->getCamera().move(Direction::FORWARD);
      break;
    case Qt::Key_S:
      this->_scene->getCamera().move(Direction::BACKWARD);
      break;
    case Qt::Key_A:
      this->_scene->getCamera().move(Direction::LEFT);
      break;
    case Qt::Key_D:
      this->_scene->getCamera().move(Direction::RIGHT);
      break;
  }
}

void OpenGLWindow::keyReleaseEvent(QKeyEvent *e) {
  switch (e->key()) {
    case Qt::Key_W:
      this->_scene->getCamera().undoMove(Direction::FORWARD);
      break;
    case Qt::Key_S:
      this->_scene->getCamera().undoMove(Direction::BACKWARD);
      break;
    case Qt::Key_A:
      this->_scene->getCamera().undoMove(Direction::LEFT);
      break;
    case Qt::Key_D:
      this->_scene->getCamera().undoMove(Direction::RIGHT);
      break;
    case Qt::Key_Escape:
      this->close();
      break;
  }
}

void OpenGLWindow::mouseMoveEvent(QMouseEvent *e) {
  QPointF point = (e->pos() - this->_center);
  float sensitivity = 0.05f;
  glm::vec3 delta = glm::vec3(point.x(), point.y(), 0.0f);
  delta *= sensitivity;
  this->_scene->getCamera().rotate(delta);

  QCursor::setPos(this->mapToGlobal(this->_center));
}
