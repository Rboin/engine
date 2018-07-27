#ifndef RENDERABLEENTITY_H
#define RENDERABLEENTITY_H

#include <memory>
#include "entity.h"
#include "renderer/renderobject.h"

class RenderableEntity : public Entity
{
public:
  RenderableEntity(Entity *e, RenderObject *r);

  std::unique_ptr<Entity> &getEntity();
  std::unique_ptr<RenderObject> &getRenderObject();

  void render(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy, const glm::mat4 &viewProjectionMatrix);

  // Entity interface
public:
  void update(const float &delta) override;
  void setPosition(glm::vec3 p) override;
  void setRotation(glm::vec3 r) override;
  void setScaling(glm::vec3 s) override;
private:
  std::unique_ptr<Entity> entity;
  std::unique_ptr<RenderObject> renderObject;
};

#endif // RENDERABLEENTITY_H
