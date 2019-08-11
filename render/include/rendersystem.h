#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "typedsystem.hpp"
#include "rendercomponent.h"
#include "renderer.h"

class RenderSystem : public TypedSystem<RenderComponent>
{
public:
    RenderSystem(Renderer *renderer);


    // TypedSystem interface
public:
    void handle(const double delta, std::unique_ptr<Entity> &entity);

private:
    std::unique_ptr<Renderer> _renderer;
};

#endif // RENDERSYSTEM_H
