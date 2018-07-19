#ifndef MOVINGENTITY_H
#define MOVINGENTITY_H

#include "entity.h"

class MovingEntity : public Entity
{
public:
  MovingEntity();
  ~MovingEntity();

  // Entity interface
public:
  void update(const int &delta) override;
  void render() override;
};

#endif // MOVINGENTITY_H
