#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <memory>
#include <vector>

#include "entity.h"

class System
{
public:
  virtual ~System() {}
  virtual void handle(const double &delta, std::vector<std::unique_ptr<Entity>> &entities) = 0;
};

#endif // SYSTEM_HPP
