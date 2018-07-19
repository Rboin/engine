#include "openglwindow.h"

#include <QFile>
#include <QOpenGLFunctions_4_3_Core>
#include <QtDebug>

#include "glm/gtc/matrix_transform.hpp"
#include "GL/gl.h"
#include "shader/shader.h"
#include "shader/shaderinformation.h"

OpenGLWindow::OpenGLWindow(QSurfaceFormat f) :
  format(f)
{
}

OpenGLWindow::~OpenGLWindow()
{
  this->makeCurrent();
}

void OpenGLWindow::setWorld(World<RenderableEntity> *world)
{
  this->world = std::unique_ptr<World<RenderableEntity>>(world);
}

void OpenGLWindow::setRenderer(Renderer *renderer)
{
  this->renderer = std::unique_ptr<Renderer>(renderer);
}

void OpenGLWindow::initializeGL()
{
  this->initializeFunctionProxy();
  char *version = (char *) this->functions->glGetString(GL_VERSION);
  char *glslVersion = (char *) this->functions->glGetString(GL_SHADING_LANGUAGE_VERSION);
  qDebug() << "Initialized with OpenGL version:"
           << version
           << "GLSL:"
           << glslVersion;

  this->functions->glViewport(0, 0, this->width(), this->height());
}

void OpenGLWindow::resizeGL(int w, int h)
{
  qDebug() << "Resizing OpenGL window...";
  if (this->world) {
    this->renderer->getCamera()->updateViewMatrix();
    this->renderer->getCamera()->updateProjectionMatrix(w, h);
  }
  this->functions->glViewport(0, 0, this->width(), this->height());
}

void OpenGLWindow::paintGL()
{

  bool isInitialized = this->renderer && this->functions;

  if (isInitialized && this->running) {
    char *version = (char *) this->functions->glGetString(GL_VERSION);
    char *glslVersion = (char *) this->functions->glGetString(GL_SHADING_LANGUAGE_VERSION);
    qDebug() << "Rendering with OpenGL version:"
             << version
             << "GLSL:"
             << glslVersion;
    this->renderer->render(this->world);
  }
}

void OpenGLWindow::initializeFunctionProxy()
{
  // Get current OpenGL context.
  this->context()->setFormat(this->format);
  if(this->context()->create()) {
    this->context()->makeCurrent(this);
    QOpenGLFunctions_4_3_Core *f = this->context()->versionFunctions<QOpenGLFunctions_4_3_Core>();
    if(!f) {
      qWarning() << "Could not get the version functions...";
    }
    f->initializeOpenGLFunctions();
    this->functions = std::make_shared<QtOpenGLProxy>(f);
    if (!this->renderer->hasFunctions()) {
      this->renderer->setFunctions(this->functions);
    }
    this->initializeShader();
    QTimer *t = new QTimer(this);
    this->timer = std::unique_ptr<QTimer>(t);
    this->connect(t, SIGNAL(timeout()), this, SLOT(update()));
    this->timer->start(0);
    this->running = true;
  }
}

void OpenGLWindow::initializeShader()
{
  QFile vertexfile(":/resources/shader/vertex.vert"), fragmentFile(":/resources/shader/fragment.frag");
  bool open = vertexfile.open(QFile::ReadOnly | QFile::Text) | fragmentFile.open(QFile::ReadOnly | QFile::Text);
  if(!open) {
    qDebug() << "Could not open shader files...";
    return;
  }
  QTextStream vertexStream(&vertexfile), fragmentStream(&fragmentFile);
  QString vertexSource = vertexStream.readAll(), fragmentSource = fragmentStream.readAll();
  vertexStream.flush();
  fragmentStream.flush();
  vertexfile.close();
  fragmentFile.close();
  this->renderer->addShader(
    new Shader(
      new ShaderInformation(
        vertexSource.toStdString(),
        fragmentSource.toStdString()
      )
    )
  );
}

//bool OpenGLWindow::event(QEvent *event)
//{
//  switch(event->type()) {
//  case QEvent::UpdateRequest:
//    update();
//    return true;
//  default:
//    return QOpenGLWindow::event(event);
//  }
//}
