#ifndef RENDERER_H
#define RENDERER_H

#include <memory>
#include "typedsystem.hpp"

#include "shader.h"
#include "openglfunctionproxy.h"
#include "glm/glm.hpp"
#include "world.h"
#include "camera.hpp"
#include "rendercomponent.h"

typedef std::unique_ptr<Entity> UniqueEntityPtr;
typedef const std::vector<std::unique_ptr<Entity>> EntityVector;
typedef std::vector<std::unique_ptr<Entity>>::const_iterator EntityVectorIterator;

class Renderer : public TypedSystem<RenderComponent>
{
public:
  Renderer(std::shared_ptr<Camera> c);
  ~Renderer();
  bool hasFunctions();
  void setFunctions(std::shared_ptr<OpenGLFunctionProxy> f);
  void initialize();
  void initializeRenderObjects(std::vector<std::unique_ptr<Entity>> &entities);
  void initializeRenderObjects(std::unique_ptr<World> &world);
  void addShader(Shader *_shader);

  void render(std::unique_ptr<World> &world);

  std::shared_ptr<Camera> &getCamera();
private:
  bool _initialized;
  int u_cameraPosition;
  GLuint _program;
  glm::mat4 _currentViewProjection;
  std::unique_ptr<Shader> _shader;
  std::shared_ptr<Camera> _camera;
  std::shared_ptr<OpenGLFunctionProxy> _proxy;

  // TypedSystem interface
public:
  // Renders each entity according to its RenderComponent
  virtual void update(const float &delta, std::unique_ptr<Entity> &entity) override;

  // System interface
public:
  virtual void update(const float &delta, std::vector<std::unique_ptr<Entity> > &entities) override;
};

#endif // RENDERER_H
