#ifndef TRANSFORMATIONSYSTEM_H
#define TRANSFORMATIONSYSTEM_H

#include "typedsystem.hpp"



class TransformationSystem : public TypedSystem<TransformComponent>
{
public:
  TransformationSystem();

  // TypedSystem interface
public:
  virtual void update(const float &delta, std::unique_ptr<Entity> &entity) override;
};

#endif // TRANSFORMATIONSYSTEM_H
