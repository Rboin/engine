#include "openglwindow.h"

#include <QFile>
#include <QOpenGLFunctions_4_3_Core>
#include <QResizeEvent>
#include <QtDebug>

#include "glm/gtc/matrix_transform.hpp"
#include "GL/gl.h"
#include "shader/shader.h"
#include "shader/shaderinformation.h"

OpenGLWindow::OpenGLWindow(QSurfaceFormat f, QWindow *parent) :
  QWindow (parent)
{
  this->setSurfaceType(QWindow::OpenGLSurface);
  this->setFormat(f);
  this->create();
  this->_lastNanos = 0;
}

OpenGLWindow::~OpenGLWindow()
{
  this->openglContext->makeCurrent(this);
}

void OpenGLWindow::initialize()
{
  this->initializeFunctionProxy();
  this->initializeShader();
  this->initializeTimer();
}

void OpenGLWindow::setWorld(World<RenderableEntity> *world)
{
  this->world = std::unique_ptr<World<RenderableEntity>>(world);
}

void OpenGLWindow::setRenderer(Renderer *renderer)
{
  this->renderer = std::unique_ptr<Renderer>(renderer);
}

void OpenGLWindow::update()
{
  long long elapsed = this->_elapsedTimer->nsecsElapsed();
  double deltaSeconds = static_cast<double>(elapsed - this->_lastNanos) / 1000000000;

  qDebug() << "Updating with delta: " << deltaSeconds;
  this->world->update(deltaSeconds);
  this->_lastNanos = elapsed;
}

void OpenGLWindow::render()
{
  if (isExposed()) {
    this->openglContext->makeCurrent(this);
    this->renderer->render(this->world);
    this->openglContext->swapBuffers(this);
  }
}

void OpenGLWindow::initializeFunctionProxy()
{
  // Get current OpenGL context.
  this->openglContext = std::make_unique<QOpenGLContext>(this);
  this->openglContext->setFormat(this->requestedFormat());
  bool created = this->openglContext->create();
  if(created) {
    this->openglContext->makeCurrent(this);
    QOpenGLFunctions_4_3_Core *f = this->openglContext->versionFunctions<QOpenGLFunctions_4_3_Core>();
    if(!f) {
      qWarning() << "Could not get the version functions...";
    }
    f->initializeOpenGLFunctions();
    this->functions = std::make_shared<QtOpenGLProxy>(f);
    if (!this->renderer->hasFunctions()) {
      this->renderer->setFunctions(this->functions);
    }

    const char *glVersion = (const char *) this->functions->glGetString(GL_VERSION),
                *glslVersion = (const char *) this->functions->glGetString(GL_SHADING_LANGUAGE_VERSION);
    qDebug() << "Initialized OpenGL with version:"
             << glVersion
             << "GLSL:"
             << glslVersion;
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

void OpenGLWindow::initializeTimer()
{
  this->_renderTimer = std::make_unique<QTimer>(this);
  this->_updateTimer = std::make_unique<QTimer>(this);
  this->_elapsedTimer = std::make_unique<QElapsedTimer>();

  this->connect(this->_updateTimer.get(), SIGNAL(timeout()), this, SLOT(update()));
  this->connect(this->_renderTimer.get(), SIGNAL(timeout()), this, SLOT(render()));

  this->_updateTimer->start();
  this->_renderTimer->start();
  this->_elapsedTimer->start();
}

void OpenGLWindow::resizeEvent(QResizeEvent *e)
{
  int width = e->size().width(),
      height = e->size().height();
  this->functions->glViewport(0, 0, width, height);
  this->renderer->getCamera()->updateViewMatrix();
  this->renderer->getCamera()->updateProjectionMatrix(width, height);
}
