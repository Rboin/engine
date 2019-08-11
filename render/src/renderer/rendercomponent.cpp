#include "rendercomponent.h"

RenderComponent::RenderComponent(OwnerId owner,
                                 RenderObjects::BaseRenderObject *r)
    : TypedComponent(owner) {
  this->_renderObject = std::shared_ptr<RenderObjects::BaseRenderObject>(r);
}

RenderObjects::BaseRenderObject &RenderComponent::getRenderObject() {
  return *this->_renderObject;
}

void RenderComponent::render(unsigned int program,
                             std::shared_ptr<OpenGLFunctionProxy> proxy,
                             Entity &entity, const glm::mat4 &viewProjection) {
  ComponentMap &componentList = entity.getComponents();
  TransformComponent &transformComponent =
      componentList.getComponent<TransformComponent>();
  const glm::mat4 &modelMatrix = transformComponent.getModel();
  this->_renderObject->render(program, proxy, modelMatrix, viewProjection);
}
