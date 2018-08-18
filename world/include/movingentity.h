#ifndef MOVINGENTITY_H
#define MOVINGENTITY_H

#include "typedentity.hpp"

class MovingEntity : public TypedEntity<MovingEntity>
{
public:
  MovingEntity();
  ~MovingEntity() override;

  // Entity interface
public:
  void update(const float &delta) override;
};

#endif // MOVINGENTITY_H
