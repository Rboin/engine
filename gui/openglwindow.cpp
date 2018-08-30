#include "openglwindow.h"

#include <QFile>
#include <QOpenGLExtraFunctions>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_3_Core>
#include <QResizeEvent>
#include <QtDebug>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/gl.h>

#include "shader.h"
#include "shaderinformation.h"

OpenGLWindow::OpenGLWindow(QWindow *parent, QSurfaceFormat f) : OpenGLWindow(parent)
{
  this->setSurfaceType(QWindow::OpenGLSurface);
  this->setFormat(f);
  this->create();
  this->setCursor(Qt::BlankCursor);
  this->_lastNanos = 0;
}

OpenGLWindow::OpenGLWindow(QWindow *parent) : QWindow(parent)
{

}

OpenGLWindow::~OpenGLWindow()
{
  if (this->openglContext) {
    this->openglContext->makeCurrent(this);
  }
}

void OpenGLWindow::initialize()
{
  this->createFunctionProxy();
  this->createShader();
  this->initializeTimer();
}

void OpenGLWindow::setWorld(World *world)
{
  this->world = std::unique_ptr<World>(world);
}

void OpenGLWindow::setCamera(std::shared_ptr<Camera> camera)
{
  this->camera = camera;
}

void OpenGLWindow::update()
{
  long long elapsed = this->_elapsedTimer->nsecsElapsed();
  double deltaSeconds = static_cast<double>(elapsed - this->_lastNanos) / 1000000000;

//  qDebug() << "Updating with delta: " << deltaSeconds;
  if (this->world && isExposed()) {
    this->openglContext->makeCurrent(this);
    this->world->update(deltaSeconds);
    this->openglContext->swapBuffers(this);
  }
  this->_lastNanos = elapsed;
}

std::shared_ptr<OpenGLFunctionProxy> OpenGLWindow::createFunctionProxy()
{
  // Get current OpenGL context.
  this->openglContext = std::make_unique<QOpenGLContext>(this);
  this->openglContext->setFormat(this->requestedFormat());
  bool created = this->openglContext->create();
  if(created) {
    this->openglContext->makeCurrent(this);
    QOpenGLExtraFunctions *f = this->openglContext->extraFunctions();
    if(!f) {
      qWarning() << "Could not get the version functions...";
    }
    f->initializeOpenGLFunctions();
    this->functions = std::make_shared<QtOpenGLProxy<QOpenGLExtraFunctions>>(f);
    const char *glVersion = (const char *) this->functions->glGetString(GL_VERSION),
                *glslVersion = (const char *) this->functions->glGetString(GL_SHADING_LANGUAGE_VERSION);
    qDebug() << "Initialized OpenGL with version:"
             << glVersion
             << "GLSL:"
             << glslVersion;
  }
  return this->functions;
}

Shader *OpenGLWindow::createShader()
{
  QFile vertexfile(":/resources/shader/vertex.vert"), fragmentFile(":/resources/shader/fragment.frag");
  bool open = vertexfile.open(QFile::ReadOnly | QFile::Text) | fragmentFile.open(QFile::ReadOnly | QFile::Text);
  if(!open) {
    qDebug() << "Could not open shader files...";
    return nullptr;
  }
  QTextStream vertexStream(&vertexfile), fragmentStream(&fragmentFile);
  QString vertexSource = vertexStream.readAll(), fragmentSource = fragmentStream.readAll();
  vertexStream.flush();
  fragmentStream.flush();
  vertexfile.close();
  fragmentFile.close();
  Shader *shader = new Shader(new ShaderInformation(vertexSource.toStdString(), fragmentSource.toStdString()));
  return shader;
}

void OpenGLWindow::initializeTimer()
{
//  this->_renderTimer = std::make_unique<QTimer>(this);
  this->_updateTimer = std::make_unique<QTimer>(this);
  this->_elapsedTimer = std::make_unique<QElapsedTimer>();

  this->connect(this->_updateTimer.get(), SIGNAL(timeout()), this, SLOT(update()));
//  this->connect(this->_renderTimer.get(), SIGNAL(timeout()), this, SLOT(render()));

  this->_updateTimer->start();
//  this->_renderTimer->start();
  this->_elapsedTimer->start();
}

void OpenGLWindow::resizeEvent(QResizeEvent *e)
{
  if (this->camera) {
    int width = e->size().width(),
        height = e->size().height();
    this->functions->glViewport(0, 0, width, height);
    this->camera->updateViewMatrix();
    this->camera->updateProjectionMatrix(width, height);
    QSize currentSize = this->size();
    this->_center = QPoint(currentSize.width()/2, currentSize.height()/2);
  }
}

void OpenGLWindow::keyPressEvent(QKeyEvent *e)
{
  if (this->camera) {
    switch(e->key()) {
    case Qt::Key_W:
      this->camera->move(Direction::FORWARD);
      break;
    case Qt::Key_S:
      this->camera->move(Direction::BACKWARD);
      break;
    case Qt::Key_A:
      this->camera->move(Direction::LEFT);
      break;
    case Qt::Key_D:
      this->camera->move(Direction::RIGHT);
      break;
    }
  }
}

void OpenGLWindow::keyReleaseEvent(QKeyEvent *e)
{
  switch (e->key()) {
  case Qt::Key_W:
    this->camera->undoMove(Direction::FORWARD);
    break;
  case Qt::Key_S:
    this->camera->undoMove(Direction::BACKWARD);
    break;
  case Qt::Key_A:
    this->camera->undoMove(Direction::LEFT);
    break;
  case Qt::Key_D:
    this->camera->undoMove(Direction::RIGHT);
    break;
  case Qt::Key_Escape:
    this->close();
    break;
  }
}

void OpenGLWindow::mouseMoveEvent(QMouseEvent *e)
{
  if (this->camera) {

    QPointF point = (e->pos() - this->_center);
    float sensitivity = 0.05f;
    glm::vec3 delta = glm::vec3(point.x(), point.y(), 0.0f);
    delta *= sensitivity;
    this->camera->rotate(delta);

    QCursor::setPos(this->mapToGlobal(this->_center));
  }
}
