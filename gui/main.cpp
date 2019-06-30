
#include <iostream>
#include <QApplication>
#include <QFile>
#include <QFileInfo>
#include <pointlight.h>
#include <directionallight.h>

#include "lightrenderobject.h"
#include "transformcomponent.h"
#include "componentlist.hpp"
#include "rendercomponent.h"

#include "playableentity.h"
#include "openglwindow.h"
#include "fpscamera.h"
#include "qtopenglproxy.hpp"

#include "transformationsystem.h"

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

Entity *createEntity(glm::vec3 position, glm::vec3 rotation, glm::vec3 scaling)
{
  Entity *e = new Entity;
  e->addComponent(new TransformComponent(e->getId(), position, rotation, scaling));
  return e;
}

template<class T>
T *createRenderObject(float shinePower,
                      const char *diffusePath, const char *specularPath, const char *emissionPath,
                      glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
  std::vector<glm::vec3> vertices = {
    // Positions
    // BACK
    glm::vec3(-0.5f, -0.5f, -0.5f),
    glm::vec3(0.5f, 0.5f, -0.5f),
    glm::vec3(0.5f,  -0.5f, -0.5f),
    glm::vec3(0.5f,  0.5f, -0.5f),
    glm::vec3(-0.5f,  -0.5f, -0.5f),
    glm::vec3(-0.5f,  0.5f, -0.5f),
    // FRONT
    glm::vec3(-0.5f, -0.5f,  0.5f),
    glm::vec3(0.5f, -0.5f,  0.5f),
    glm::vec3(0.5f,  0.5f,  0.5f),
    glm::vec3(0.5f,  0.5f,  0.5f),
    glm::vec3(-0.5f,  0.5f,  0.5f),
    glm::vec3(-0.5f, -0.5f,  0.5f),
    // LEFT
    glm::vec3(-0.5f,  0.5f,  0.5f),
    glm::vec3(-0.5f,  0.5f, -0.5f),
    glm::vec3(-0.5f, -0.5f, -0.5f),
    glm::vec3(-0.5f, -0.5f, -0.5f),
    glm::vec3(-0.5f, -0.5f,  0.5f),
    glm::vec3(-0.5f,  0.5f,  0.5f),
    // RIGHT
    glm::vec3(0.5f,  0.5f,  0.5f),
    glm::vec3(0.5f,  -0.5f, -0.5f),
    glm::vec3(0.5f, 0.5f, -0.5f),
    glm::vec3(0.5f, -0.5f, -0.5f),
    glm::vec3(0.5f, 0.5f,  0.5f),
    glm::vec3(0.5f,  -0.5f,  0.5f),
    // BOTTOM
    glm::vec3(-0.5f, -0.5f, -0.5f),
    glm::vec3(0.5f, -0.5f, -0.5f),
    glm::vec3(0.5f, -0.5f,  0.5f),
    glm::vec3(0.5f, -0.5f,  0.5f),
    glm::vec3(-0.5f, -0.5f,  0.5f),
    glm::vec3(-0.5f, -0.5f, -0.5f),
    // TOP
    glm::vec3(-0.5f,  0.5f, -0.5f),
    glm::vec3(0.5f,  0.5f, 0.5f),
    glm::vec3(0.5f,  0.5f,  -0.5f),
    glm::vec3(0.5f,  0.5f,  0.5f),
    glm::vec3(-0.5f,  0.5f,  -0.5f),
    glm::vec3(-0.5f,  0.5f, 0.5f),

    // Colors
    glm::vec3(1.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 1.0f),
    glm::vec3(1.0f, 1.0f, 0.0f),

    // Texture coordinates
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(1.0f, 1.0f, 0.0f),
    glm::vec3(1.0f, 0.0f, 0.0f),
    glm::vec3(1.0f, 1.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f),

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
    glm::vec3(0.0f, 1.0f, 0.0f),
    glm::vec3(1.0f, 1.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f),
    glm::vec3(1.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),

    glm::vec3(0.0f, 1.0f, 0.0f),
    glm::vec3(1.0f, 1.0f, 0.0f),
    glm::vec3(1.0f, 0.0f, 0.0f),
    glm::vec3(1.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f),

    glm::vec3(0.0f, 1.0f, 0.0f),
    glm::vec3(1.0f, 0.0f, 0.0f),
    glm::vec3(1.0f, 1.0f, 0.0f),
    glm::vec3(1.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),

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

World *createWorld()
{
  return new World;
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
  format.setDepthBufferSize(24);
  QSurfaceFormat::setDefaultFormat(format);
  OpenGLWindow window(nullptr, format);

  std::shared_ptr<Camera> camera = std::shared_ptr<FPSCamera>(new FPSCamera({45.0f, 0.1f, 100.0f}, glm::vec3(-2.0f, 0.0f, -1.0f)));
  camera->setRotation(glm::vec3(90.0f, 0.0f, 0.0f));


  // BOX
  RenderObjects::BaseRenderObject *ro = createRenderObject<RenderObjects::BaseRenderObject>(32.0f,
                                                                                            ":/resources/images/steelborder_woodbox.png",
                                                                                            ":/resources/images/container2_specular.png",
                                                                                            ":/resources/images/matrix.jpg",
                                                                                            glm::vec3(1.0f, 0.5f, 0.31f),
                                                                                            glm::vec3(1.0f, 0.5f, 0.31f),
                                                                                            glm::vec3(0.5f, 0.5f, 0.5f));
  auto *box = new Entity;
  box->addComponent(
    new TransformComponent(
      box->getId(),
      glm::vec3(0.0f),
      glm::vec3(0.0f),
      glm::vec3(1.0f)
    )
  );
  box->addComponent(new RenderComponent(box->getId(), ro));

  // BOX2
  RenderObjects::BaseRenderObject *ro2 = createRenderObject<RenderObjects::BaseRenderObject>(32.0f,
                                                                                            ":/resources/images/steelborder_woodbox.png",
                                                                                            ":/resources/images/container2_specular.png",
                                                                                            ":/resources/images/matrix.jpg",
                                                                                            glm::vec3(1.0f, 0.5f, 0.31f),
                                                                                            glm::vec3(1.0f, 0.5f, 0.31f),
                                                                                            glm::vec3(0.5f, 0.5f, 0.5f));
  auto *box2 = new Entity;
  box2->addComponent(
    new TransformComponent(
      box2->getId(),
      glm::vec3(2.0f, 0.0f, 0.0f),
      glm::vec3(0.0f),
      glm::vec3(1.0f)
    )
  );
  box2->addComponent(new RenderComponent(box2->getId(), ro2));


  // LIGHT OBJECT (pointlights)
  RenderObjects::PointLight *lightRenderObject1 = createRenderObject<RenderObjects::PointLight>(-1,
                                                                                                ":/resources/images/awesomeface.png",
                                                                                                ":/resources/images/awesomeface.png",
                                                                                                ":/resources/images/default.png",
                                                                                                glm::vec3(0.2f, 0.2f, 0.2f),
                                                                                                glm::vec3(0.5f, 0.5f, 0.5f),
                                                                                                glm::vec3(1.0f, 1.0f, 1.0f));
  lightRenderObject1->setIndex(0);
  auto *light1 = new Entity;
  light1->addComponent(
    new TransformComponent(
      light1->getId(),
      glm::vec3(0.0f, 0.5f, -1.0f),
      glm::vec3(0.0f),
      glm::vec3(0.1f)
    ));
  light1->addComponent(new RenderComponent(light1->getId(), lightRenderObject1));

  RenderObjects::PointLight *lightRenderObject2 = createRenderObject<RenderObjects::PointLight>(-1,
                                                                                                ":/resources/images/awesomeface.png",
                                                                                                ":/resources/images/awesomeface.png",
                                                                                                ":/resources/images/default.png",
                                                                                                glm::vec3(0.2f, 0.2f, 0.2f),
                                                                                                glm::vec3(0.5f, 0.5f, 0.5f),
                                                                                                glm::vec3(1.0f, 1.0f, 1.0f));
  lightRenderObject2->setIndex(1);
  auto *light2 = new Entity;
  light2->addComponent(
    new TransformComponent(
      light2->getId(),
      glm::vec3(0.0f, 0.5f, 1.0f),
      glm::vec3(0.0f),
      glm::vec3(0.1f)
    ));
  light2->addComponent(new RenderComponent(light2->getId(), lightRenderObject2));

  // Directional light
  RenderObjects::DirectionalLight *dirLightRenderObject = createRenderObject<RenderObjects::DirectionalLight> (-1,
                                                                                                               ":/resources/images/crate.png",
                                                                                                               ":/resources/images/crate.png",
                                                                                                               ":/resources/images/crate.png",
                                                                                                               glm::vec3(1.0f, 1.0f, 1.0f),
                                                                                                               glm::vec3(1.0f, 1.0f, 1.0f),
                                                                                                               glm::vec3(1.0f, 1.0f, 1.0f));

  auto dirLight = new Entity;
  dirLight->addComponent(new TransformComponent(
                           dirLight->getId(),
                           glm::vec3(1.0f, 0.5f, 0.0f),
                           glm::vec3(0.0f),
                           glm::vec3(0.1f)
                         ));
  dirLight->addComponent(new RenderComponent(dirLight->getId(), dirLightRenderObject));

  // PLAYER
  RenderObjects::BaseRenderObject *playerRenderObject = createRenderObject<RenderObjects::BaseRenderObject>(1,
                                                                                                            ":/resources/images/crate.png",
                                                                                                            ":/resources/images/crate.png",
                                                                                                            ":/resources/images/crate.png",
                                                                                                            glm::vec3(1.0f, 0.0f, 0.0f),
                                                                                                            glm::vec3(0.0f, 1.0f, 0.0f),
                                                                                                            glm::vec3(0.0f, 0.0f, 1.0f));
  auto *player = new PlayableEntity(camera);
  player->addComponent(
    new TransformComponent(
      player->getId(),
      camera->getPosition(),
      camera->getRotationVector(),
      glm::vec3(1.0f)
    ));
  player->addComponent(new RenderComponent(player->getId(), playerRenderObject));



  World *world = createWorld();
  world->addEntity(box);
  world->addEntity(box2);
  world->addEntity(player);

  Renderer *renderer = new Renderer();

  Scene *scene = new Scene(camera, std::shared_ptr<World>(world));
  scene->addDirectionalLight(dirLight);
  scene->addPointLight(light1);
  scene->addPointLight(light2);

  window.setRenderer(renderer);
  window.setScene(scene);
  window.setHeight(720);
  window.setWidth(1280);

  // Add systems to the world.
  world->addSystem(new TransformationSystem);

  window.initialize();
  window.show();

  return app.exec();
}
