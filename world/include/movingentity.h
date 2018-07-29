#ifndef MOVINGENTITY_H
#define MOVINGENTITY_H

#include "entity.h"

class MovingEntity : public Entity
{
public:
  MovingEntity(std::shared_ptr<Axis> &a);
  ~MovingEntity() override;

  // Entity interface
public:
  void update(const float &delta) override;
};

#endif // MOVINGENTITY_H
