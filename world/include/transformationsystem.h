#ifndef TRANSFORMATIONSYSTEM_H
#define TRANSFORMATIONSYSTEM_H

#include "typedsystem.hpp"
#include "transformcomponent.h"

class TransformationSystem : public TypedSystem<TransformComponent>
{
public:
  TransformationSystem();

  // TypedSystem interface
public:
  virtual void handle(const double delta, std::unique_ptr<Entity> &entity) override;
};

#endif // TRANSFORMATIONSYSTEM_H
