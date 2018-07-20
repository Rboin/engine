#ifndef MOVINGENTITY_H
#define MOVINGENTITY_H

#include "entity.h"

class MovingEntity : public Entity
{
public:
  MovingEntity();
  ~MovingEntity() override;

  // Entity interface
public:
  void update(const double &delta) override;
};

#endif // MOVINGENTITY_H
