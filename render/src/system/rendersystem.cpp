#include "rendersystem.h"

RenderSystem::RenderSystem(Renderer *renderer)
{
    this->_renderer = std::unique_ptr<Renderer>(renderer);
}

void RenderSystem::handle(const double delta, std::unique_ptr<Entity> &entity)
{
    RenderComponent *renderComponent = entity->getComponents()->getComponent<RenderComponent>();
//    renderComponent->render();
}
