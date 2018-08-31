#include "rendercomponent.h"

RenderComponent::RenderComponent(OwnerId owner, RenderObjects::BaseRenderObject *r) : TypedComponent(owner)
{
  this->_renderObject = std::shared_ptr<RenderObjects::BaseRenderObject>(r);
}

std::shared_ptr<RenderObjects::BaseRenderObject> RenderComponent::getRenderObject()
{
  return this->_renderObject;
}

void RenderComponent::render(unsigned int program,
                             std::shared_ptr<OpenGLFunctionProxy> proxy,
                             Entity &entity,
                             const glm::mat4 &viewProjection)
{
  std::shared_ptr<ComponentMap> componentList = entity.getComponents();
  std::shared_ptr<TransformComponent> transformComponent = componentList->getComponent<TransformComponent>();
  if (transformComponent != nullptr) {
    const glm::mat4 &modelMatrix = transformComponent->getModel();
    this->_renderObject->render(program, proxy, modelMatrix, viewProjection);
  }
}
