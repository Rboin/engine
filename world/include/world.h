#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <memory>
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#include "component.hpp"
#include "system.h"

class World
{
public:
  World()
  {
    this->_entities = std::vector<std::unique_ptr<Entity>>();
    this->_systems = std::vector<std::unique_ptr<System>>();
  }

  void addEntity(Entity *entity)
  {
    this->_entities.push_back(std::unique_ptr<Entity>(entity));
  }

  void removeEntity(Entity *entity)
  {
    this->_entities.erase(
      std::remove_if(
        this->_entities.begin(),
        this->_entities.end(),
    [&] (std::unique_ptr<Entity> &e) {
      return entity == e.get();
    }),
    this->_entities.end()
    );
  }

  std::vector<std::unique_ptr<Entity>> &getEntities()
  {
    return this->_entities;
  }

  void addSystem(System *h)
  {
    this->_systems.push_back(std::unique_ptr<System>(h));
  }

  void removeSystem(System *h)
  {
    this->_systems.erase(
      std::remove_if(
        this->_systems.begin(),
        this->_systems.end(),
    [&] (std::unique_ptr<System> &handler) {
      return h == handler.get();
    }),
    this->_systems.end()
    );
  }

  std::vector<std::unique_ptr<System>> &getSystems()
  {
    return this->_systems;
  }

private:
  std::unique_ptr<Entity> _light;
  std::vector<std::unique_ptr<Entity>> _entities;
  std::vector<std::unique_ptr<System>> _systems;
};

#endif // WORLD_H
