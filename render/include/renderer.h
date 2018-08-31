#ifndef RENDERER_H
#define RENDERER_H

#include <memory>

#include "shader.h"
#include "openglfunctionproxy.h"
#include "glm/glm.hpp"
#include "world.h"
#include "camera.hpp"
#include "rendercomponent.h"
#include "scene.h"

typedef std::unique_ptr<Entity> UniqueEntityPtr;
typedef std::vector<std::unique_ptr<Entity>> EntityVector;
typedef std::vector<std::unique_ptr<Entity>>::iterator EntityVectorIterator;

class Renderer
{
public:
  Renderer();
  ~Renderer();
  bool hasFunctions();
  void setFunctions(std::shared_ptr<OpenGLFunctionProxy> f);
  std::shared_ptr<OpenGLFunctionProxy> getFunctionProxy();
  void initialize();
  void addShader(Shader *_shader);

  void render(std::unique_ptr<Scene> &scene);
  void renderEntities(std::vector<std::unique_ptr<Entity> > &entities);
  void renderLights(std::vector<std::unique_ptr<Entity>> &lights);
  void renderEntity(std::unique_ptr<Entity> &entity);
private:
  bool _initialized;
  int u_cameraPosition;
  GLuint _program;
  glm::mat4 _currentViewProjection;
  std::unique_ptr<Shader> _shader;
  std::shared_ptr<OpenGLFunctionProxy> _proxy;
};

#endif // RENDERER_H
