#ifndef RENDERER_H
#define RENDERER_H

#include <memory>

#include "shader.h"
#include "openglfunctionproxy.h"
#include "glm/glm.hpp"
#include "world.hpp"
#include "camera.hpp"
#include "rendercomponent.h"

typedef std::unique_ptr<Entity> UniqueEntityPtr;
typedef const std::vector<std::unique_ptr<Entity>> EntityVector;
typedef std::vector<std::unique_ptr<Entity>>::const_iterator EntityVectorIterator;

class Renderer
{
public:
  Renderer(std::shared_ptr<Camera> c);
  ~Renderer();
  bool hasFunctions();
  void setFunctions(std::shared_ptr<OpenGLFunctionProxy> f);
  void initialize();
  void initializeRenderObjects(std::unique_ptr<World<Entity> > &world);
  void addShader(Shader *_shader);

  void render(std::unique_ptr<World<Entity> > &world);

  std::shared_ptr<Camera> &getCamera();
private:
  bool _initialized;
  int u_cameraPosition;
  GLuint _program;
  std::unique_ptr<Shader> _shader;
  std::shared_ptr<Camera> _camera;
  std::shared_ptr<OpenGLFunctionProxy> _proxy;
};

#endif // RENDERER_H
