#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#include <memory>

#include <transformcomponent.h>
#include <typedcomponent.hpp>

#include "renderobject.h"

class RenderComponent : public TypedComponent<RenderComponent> {
 public:
  RenderComponent(OwnerId owner, RenderObjects::BaseRenderObject *r);

  RenderObjects::BaseRenderObject &getRenderObject();

  void render(unsigned int program, std::shared_ptr<OpenGLFunctionProxy> proxy,
              Entity &entity, const glm::mat4 &viewProjection);

 private:
  std::shared_ptr<RenderObjects::BaseRenderObject> _renderObject;
};

#endif  // RENDERCOMPONENT_H
