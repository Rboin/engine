
#include <iostream>
#include <QApplication>
#include <QFile>
#include <QFileInfo>
#include <lightrenderobject.h>

#include "movingentity.h"
#include "playableentity.h"
#include "openglwindow.h"
#include "fpscamera.h"
#include "qtopenglproxy.hpp"

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
T *createRenderObject(float shinePower,
                      const char *diffusePath, const char *specularPath, const char *emissionPath,
                      glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
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
  TextureImage *diffuseTexture = loadImage(diffusePath, GL_RGBA, GL_RGB, 4);
  TextureImage *specularTexture = loadImage(specularPath, GL_RGBA, GL_RGB, 4);
  TextureImage *emissionTexture = loadImage(emissionPath, GL_RGBA, GL_RGBA, 4);
  Texture *t = new Texture();
  t->setDiffuseTexture(diffuseTexture);
  t->setSpecularTexture(specularTexture);
  t->setEmissionTexture(emissionTexture);

  Material *mat = new Material(shinePower, t, ambient, diffuse, specular);
  Mesh *m = new Mesh(0, v, mat);
  T *r = new T(m);
  return r;
}

World<RenderableEntity> *createWorld()
{

  RenderableEntity *entity = new RenderableEntity(createEntity(glm::vec3(0.0f, 0.0f, 0.0f),
                                                               glm::vec3(0.0f, 0.0f, 0.0f),
                                                               glm::vec3(1.0f, 1.0f, 1.0f),
                                                               glm::vec3(0.0f, 1.0f, 0.0f),
                                                               glm::vec3(0.0f, 0.0f, -1.0f),
                                                               glm::vec3(1.0f, 0.0f, 0.0f)),
                                                  createRenderObject<RenderObject>(32.0f,
                                                                                   ":/resources/images/steelborder_woodbox.png",
                                                                                   ":/resources/images/container2_specular.png",
                                                                                   ":/resources/images/matrix.jpg",
                                                                                   glm::vec3(1.0f, 0.5f, 0.31f),
                                                                                   glm::vec3(1.0f, 0.5f, 0.31f),
                                                                                   glm::vec3(0.5f, 0.5f, 0.5f)));

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
  {glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)});

  RenderableEntity *light1 = new RenderableEntity(createEntity(glm::vec3(0.0f, 0.5f, -1.0f),
                                                               glm::vec3(0.0f),
                                                               glm::vec3(0.1f),
                                                               glm::vec3(0.0f, 1.0f, 0.0f),
                                                               glm::vec3(0.0f, 0.0f, -1.0f),
                                                               glm::vec3(1.0f, 0.0f, 0.0f)),
                                                  createRenderObject<LightRenderObject>(-1,
                                                                                        ":/resources/images/awesomeface.png",
                                                                                        ":/resources/images/awesomeface.png",
                                                                                        ":/resources/images/default.png",
                                                                                        glm::vec3(0.2f, 0.2f, 0.2f),
                                                                                        glm::vec3(0.5f, 0.5f, 0.5f),
                                                                                        glm::vec3(1.0f, 1.0f, 1.0f)));
  std::unique_ptr<LightRenderObject> &lro1 = (std::unique_ptr<LightRenderObject> &) light1->getRenderObject();
  lro1->setIsPointLight(true);

  PlayableEntity *player = new PlayableEntity(camera, createEntity(glm::vec3(0.0f, 0.0f, 0.0f),
                                                                   glm::vec3(0.0f, 0.0f, 0.0f),
                                                                   glm::vec3(0.0f, 0.0f, 0.0f),
                                                                   glm::vec3(0.0f, 1.0f, 0.0f),
                                                                   glm::vec3(0.0f, 0.0f, -1.0f),
                                                                   glm::vec3(1.0f, 0.0f, 0.0f)),
                                              createRenderObject<RenderObject>(0,
                                                                               ":/resources/images/default.png",
                                                                               ":/resources/images/default.png",
                                                                               ":/resources/images/default.png",
                                                                               glm::vec3(0.0f, 0.0f, 0.0f),
                                                                               glm::vec3(0.0f, 0.0f, 0.0f),
                                                                               glm::vec3(0.0f, 0.0f, 0.0f)));
  Renderer renderer(player->getCamera());
  player->setAxis(camera->getAxis());
  world->addEntity(player);
  world->addEntity(light1);
  window.setRenderer(&renderer);
  window.setHeight(720);
  window.setWidth(1280);
  window.initialize();
  window.show();

  return app.exec();
}
