#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#include <memory>
#include <typedcomponent.hpp>
#include <transformcomponent.h>

#include "renderableentity.h"
#include "renderobject.h"

class RenderComponent : public TypedComponent<RenderComponent>
{
public:
  RenderComponent(OwnerId owner, RenderObject *r);

  std::shared_ptr<RenderObject> getRenderObject();

  void render(unsigned int program,
              std::shared_ptr<OpenGLFunctionProxy> proxy,
              Entity &entity,
              const glm::mat4 &viewProjection);

private:
  std::shared_ptr<RenderObject> _renderObject;

  // Component interface
public:
  virtual void update(const float &delta) override;
};

#endif // RENDERCOMPONENT_H
