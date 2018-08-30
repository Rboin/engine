#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <memory>
#include <vector>

#include "entity.hpp"

class System
{
public:
  virtual void update(const float &delta, std::vector<std::unique_ptr<Entity>> &entities) = 0;
};

#endif // SYSTEM_HPP
