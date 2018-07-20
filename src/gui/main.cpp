#include "openglwindow.h"
#include "qtopenglproxy.h"
#include "movingentity.h"

#include <QApplication>
#include <QFile>
#include <QTimer>
#include <iostream>
#include <QOpenGLTexture>
#include <QFileInfo>

TextureImage *loadImage(const char *fileName, GLenum imageFormat, GLint internalFormat, int nChannels)
{


  TextureImage *result = new TextureImage;

  QImage image;
  bool loaded = image.load(fileName);
  if (loaded) {
    if (nChannels == 3) {
      image = image.convertToFormat(QImage::Format_RGB888);
    } else {
      image = image.convertToFormat(QImage::Format_RGBA8888);
    }
    image = image.mirrored();
    result->width = image.width();
    result->height = image.height();
    unsigned char *tmp = image.bits();
    // size = width * height * channels (channels = RGBA = 4)
    int size = image.width() * image.height() * nChannels;
    result->imageData = std::vector<unsigned char>(tmp, tmp + size);
    result->imageFormat = imageFormat;
    result->internalFormat = internalFormat;
  }
  image.detach();

  return result;

}

World<RenderableEntity> *createWorld()
{
  Entity *e = new MovingEntity();

  std::vector<glm::vec3> vertices = {
    // Positions
    glm::vec3(-0.5f, -0.5f, -0.5f),
    glm::vec3(0.5f, -0.5f, -0.5f),
    glm::vec3(0.5f,  0.5f, -0.5f),
    glm::vec3(0.5f,  0.5f, -0.5f),
    glm::vec3(-0.5f,  0.5f, -0.5f),
    glm::vec3(-0.5f,  -0.5f, -0.5f),

    glm::vec3(-0.5f, -0.5f,  0.5f),
    glm::vec3(0.5f, -0.5f,  0.5f),
    glm::vec3(0.5f,  0.5f,  0.5f),
    glm::vec3(0.5f,  0.5f,  0.5f),
    glm::vec3(-0.5f,  0.5f,  0.5f),
    glm::vec3(-0.5f, -0.5f,  0.5f),

    glm::vec3(-0.5f,  0.5f,  0.5f),
    glm::vec3(-0.5f,  0.5f, -0.5f),
    glm::vec3(-0.5f, -0.5f, -0.5f),
    glm::vec3(-0.5f, -0.5f, -0.5f),
    glm::vec3(-0.5f, -0.5f,  0.5f),
    glm::vec3(-0.5f,  0.5f,  0.5f),

    glm::vec3(0.5f,  0.5f,  0.5f),
    glm::vec3(0.5f,  0.5f, -0.5f),
    glm::vec3(0.5f, -0.5f, -0.5f),
    glm::vec3(0.5f, -0.5f, -0.5f),
    glm::vec3(0.5f, -0.5f,  0.5f),
    glm::vec3(0.5f,  0.5f,  0.5f),

    glm::vec3(-0.5f, -0.5f, -0.5f),
    glm::vec3(0.5f, -0.5f, -0.5f),
    glm::vec3(0.5f, -0.5f,  0.5f),
    glm::vec3(0.5f, -0.5f,  0.5f),
    glm::vec3(-0.5f, -0.5f,  0.5f),
    glm::vec3(-0.5f, -0.5f, -0.5f),

    glm::vec3(-0.5f,  0.5f, -0.5f),
    glm::vec3(0.5f,  0.5f, -0.5f),
    glm::vec3(0.5f,  0.5f,  0.5f),
    glm::vec3(0.5f,  0.5f,  0.5f),
    glm::vec3(-0.5f,  0.5f,  0.5f),
    glm::vec3(-0.5f,  0.5f, -0.5f),

    // Colors
    glm::vec3(1.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 1.0f),
    glm::vec3(1.0f, 1.0f, 0.0f),

    // Texture coordinates
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(1.0f, 0.0f, 0.0f),
    glm::vec3(1.0f, 1.0f, 0.0f),
    glm::vec3(1.0f, 1.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),

    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(1.0f, 0.0f, 0.0f),
    glm::vec3(1.0f, 1.0f, 0.0f),
    glm::vec3(1.0f, 1.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),

    glm::vec3(1.0f, 0.0f, 0.0f),
    glm::vec3(1.0f, 1.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(1.0f, 0.0f, 0.0f),

    glm::vec3(1.0f, 0.0f, 0.0f),
    glm::vec3(1.0f, 1.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(1.0f, 0.0f, 0.0f),

    glm::vec3(0.0f, 1.0f, 0.0f),
    glm::vec3(1.0f, 1.0f, 0.0f),
    glm::vec3(1.0f, 0.0f, 0.0f),
    glm::vec3(1.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f),

    glm::vec3(0.0f, 1.0f, 0.0f),
    glm::vec3(1.0f, 1.0f, 0.0f),
    glm::vec3(1.0f, 0.0f, 0.0f),
    glm::vec3(1.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f)
  };
  std::vector<unsigned int> indices = {
    0, 1, 3,
    1, 2, 3
  };

  VertexData *vData = new VertexData;
  vData->vertexSize = 36;
  vData->indiceSize = 6;
  vData->colorSize = 4;
  vData->textureSize = 36;
  vData->vertices = vertices;
  vData->indices = indices;
  Vertex *v = new Vertex(vData);
  std::vector<glm::vec2> texture = {
    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 0.0f),
    glm::vec2(0.5f, 1.0f)
  };
  TextureImage *texture1 = loadImage(":/resources/images/container.jpg", GL_RGB, GL_RGB, 3);
  TextureImage *texture2 = loadImage(":/resources/images/awesomeface.png", GL_RGBA, GL_RGB, 4);
  Texture *t = new Texture();
  t->addTexture(texture1);
  t->addTexture(texture2);

  Material *mat = new Material(glm::vec3(1.0f, 0.0f, 0.0f),
                               glm::vec3(0.0f, 1.0f, 0.0f),
                               glm::vec3(0.0f, 0.0f, 1.0f));
  Mesh *m = new Mesh(0, v, t, mat);
  RenderObject *r = new RenderObject(m);
  RenderableEntity *entity = new RenderableEntity(e, r);
  World<RenderableEntity> *world = new World<RenderableEntity>();
  world->addEntity(entity);
  return world;
}

int main(int argc, char **argv)
{
  QApplication app(argc, argv);
  QSurfaceFormat format;
  format.setVersion(4, 3);
  format.setRenderableType(QSurfaceFormat::OpenGL);
  format.setProfile(QSurfaceFormat::CoreProfile);
  format.setSamples(4);
  QSurfaceFormat::setDefaultFormat(format);
  OpenGLWindow window(format);
  window.setWorld(createWorld());
  Camera *camera = new Camera(45.0f, 0.1f, 100.0f);
  camera->addToPosition(glm::vec3(0.0f, 0.0f, 3.0f));
  window.setRenderer(new Renderer(camera));
  window.setHeight(600);
  window.setWidth(800);
  window.show();

  return app.exec();
}
