
#include <iostream>
#include <QApplication>
#include <QFile>
#include <QFileInfo>
#include <lightrenderobject.h>

#include "movingentity.h"
#include "playableentity.h"
#include "openglwindow.h"
#include "fpscamera.h"
#include "qtopenglproxy.h"

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



Entity *createEntity(glm::vec3 position, glm::vec3 rotation, glm::vec3 scaling, glm::vec3 up, glm::vec3 forward, glm::vec3 right)
{
  std::shared_ptr<Axis> axis = std::make_shared<Axis>(up, forward, right);
  Entity *e = new MovingEntity(axis);
  e->setPosition(position);
  e->setRotation(rotation);
  e->setScaling(scaling);
  return e;
}

template<class T>
T *createRenderObject(float colorPower, glm::vec3 color)
{
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
    glm::vec3(0.0f, 1.0f, 0.0f),

    // Normals
    glm::vec3(0.0f,  0.0f, -1.0f),
    glm::vec3(0.0f,  0.0f, -1.0f),
    glm::vec3(0.0f,  0.0f, -1.0f),
    glm::vec3(0.0f,  0.0f, -1.0f),
    glm::vec3(0.0f,  0.0f, -1.0f),
    glm::vec3(0.0f,  0.0f, -1.0f),
    glm::vec3(0.0f,  0.0f, 1.0f),
    glm::vec3(0.0f,  0.0f, 1.0f),
    glm::vec3(0.0f,  0.0f, 1.0f),
    glm::vec3(0.0f,  0.0f, 1.0f),
    glm::vec3(0.0f,  0.0f, 1.0f),
    glm::vec3(0.0f,  0.0f, 1.0f),
    glm::vec3(-1.0f,  0.0f,  0.0f),
    glm::vec3(-1.0f,  0.0f,  0.0f),
    glm::vec3(-1.0f,  0.0f,  0.0f),
    glm::vec3(-1.0f,  0.0f,  0.0f),
    glm::vec3(-1.0f,  0.0f,  0.0f),
    glm::vec3(-1.0f,  0.0f,  0.0f),
    glm::vec3(1.0f,  0.0f,  0.0f),
    glm::vec3(1.0f,  0.0f,  0.0f),
    glm::vec3(1.0f,  0.0f,  0.0f),
    glm::vec3(1.0f,  0.0f,  0.0f),
    glm::vec3(1.0f,  0.0f,  0.0f),
    glm::vec3(1.0f,  0.0f,  0.0f),
    glm::vec3(0.0f, -1.0f,  0.0f),
    glm::vec3(0.0f, -1.0f,  0.0f),
    glm::vec3(0.0f, -1.0f,  0.0f),
    glm::vec3(0.0f, -1.0f,  0.0f),
    glm::vec3(0.0f, -1.0f,  0.0f),
    glm::vec3(0.0f, -1.0f,  0.0f),
    glm::vec3(0.0f,  1.0f,  0.0f),
    glm::vec3(0.0f,  1.0f,  0.0f),
    glm::vec3(0.0f,  1.0f,  0.0f),
    glm::vec3(0.0f,  1.0f,  0.0f),
    glm::vec3(0.0f,  1.0f,  0.0f),
    glm::vec3(0.0f,  1.0f,  0.0f),
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
  vData->normalSize = 36;
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

  Material *mat = new Material(colorPower, color,
                               glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
                               glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
  Mesh *m = new Mesh(0, v, t, mat);
  T *r = new T(m);
  return r;
}

World<RenderableEntity> *createWorld()
{

  RenderableEntity *entity = new RenderableEntity(createEntity(glm::vec3(0.0f, 0.0f, -2.0f),
                                                               glm::vec3(0.0f, 0.0f, 0.0f),
                                                               glm::vec3(1.0f, 1.0f, 1.0f),
                                                               glm::vec3(0.0f, 1.0f, 0.0f),
                                                               glm::vec3(0.0f, 0.0f, -1.0f),
                                                               glm::vec3(1.0f, 0.0f, 0.0f)),
                                                  createRenderObject<RenderObject>(.25f, glm::vec3(0.5f, 0.5f, 1.0f)));

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
  format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
  format.setSamples(4);
  QSurfaceFormat::setDefaultFormat(format);
  OpenGLWindow window(nullptr, format);
  World<RenderableEntity> *world = createWorld();
  window.setWorld(world);
  Camera *camera = new FPSCamera({45.0f, 0.1f, 100.0f},
  {glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)});
  RenderableEntity *light = new RenderableEntity(createEntity(glm::vec3(-1.0f, 0.0f, 0.0f),
                                                              glm::vec3(0.0f),
                                                              glm::vec3(.25f),
                                                              glm::vec3(0.0f, 1.0f, 0.0f),
                                                              glm::vec3(0.0f, 0.0f, -1.0f),
                                                              glm::vec3(1.0f, 0.0f, 0.0f)),
                                                 createRenderObject<LightRenderObject>(1.0f, glm::vec3(1.0f)));
  PlayableEntity *player = new PlayableEntity(camera, createEntity(glm::vec3(0.0f, 0.0f, 0.0f),
                                                                   glm::vec3(0.0f, 0.0f, 0.0f),
                                                                   glm::vec3(0.0f, 0.0f, 0.0f),
                                                                   glm::vec3(0.0f, 1.0f, 0.0f),
                                                                   glm::vec3(0.0f, 0.0f, -1.0f),
                                                                   glm::vec3(1.0f, 0.0f, 0.0f)),
                                              createRenderObject<RenderObject>(0.0f, glm::vec3(0.0f, 0.0f, 0.0f)));
  player->setAxis(camera->getAxis());
  world->addEntity(player);
  world->addEntity(light);
  window.setRenderer(new Renderer(player->getCamera()));
  window.setHeight(720);
  window.setWidth(1280);
  window.initialize();
  window.show();

  return app.exec();
}
