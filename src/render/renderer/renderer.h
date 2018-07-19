#ifndef RENDERER_H
#define RENDERER_H

#include <memory>
#include <shader/shader.h>
#include "renderer/openglfunctionproxy.h"
#include "glm/glm.hpp"
#include "entities/renderableentity.h"
#include "world.hpp"
#include "camera/camera.h"

typedef const std::vector<std::unique_ptr<RenderableEntity>> RenderableVector;
typedef std::vector<std::unique_ptr<RenderableEntity>>::const_iterator RenderableVectorIterator;

class Renderer
{
public:
  Renderer(Camera *c);
  ~Renderer();
  bool hasFunctions();
  void setFunctions(std::shared_ptr<OpenGLFunctionProxy> &f);
  void initialize();
  void initializeRenderObjects(std::unique_ptr<World<RenderableEntity>> &world);
  void addShader(Shader *_shader);

  void render(std::unique_ptr<World<RenderableEntity> > &world);
  void renderEntity(const std::unique_ptr<RenderableEntity> &entity, std::unique_ptr<Camera> &camera);

  std::unique_ptr<Camera> &getCamera();
private:
  bool _initialized;
  GLuint _program;
  std::unique_ptr<Shader> _shader;
  std::unique_ptr<Camera> _camera;
  std::shared_ptr<OpenGLFunctionProxy> _proxy;
};

#endif // RENDERER_H
