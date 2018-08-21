#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <memory>
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#include "componenthandler.hpp"

template<class T>
class World
{
public:
  World()
  {
    this->_entities = std::vector<std::unique_ptr<T> >();
    this->_componentHandlers = std::vector<std::unique_ptr<ComponentHandler>>();
  }

  void initialize() {}

  void setLight(T *entity)
  {
    this->_light = std::unique_ptr<T>(entity);
  }

  std::unique_ptr<T> &getLight()
  {
    return this->_light;
  }

  void addEntity(T *entity)
  {
    this->_entities.push_back(std::unique_ptr<T>(entity));
  }

  void removeEntity(T *entity)
  {
    this->_entities.erase(
      std::remove_if(
        this->_entities.begin(),
        this->_entities.end(),
    [&] (std::unique_ptr<T> &e) {
      return entity == e.get();
    }),
    this->_entities.end()
    );
  }

  void addComponentHandler(ComponentHandler *h)
  {
    this->_componentHandlers.push_back(std::unique_ptr<ComponentHandler>(h));
  }

  void removeComponentHandler(ComponentHandler *h)
  {
    this->_componentHandlers.erase(
      std::remove_if(
        this->_componentHandlers.begin(),
        this->_componentHandlers.end(),
    [&] (std::unique_ptr<ComponentHandler> &handler) {
      return h == handler.get();
    }),
    this->_componentHandlers.end()
    );
  }

  const std::vector<std::unique_ptr<T>> &getEntities() const
  {
    return this->_entities;
  }

  void update(const double &delta)
  {

    typename std::vector<std::unique_ptr<T>>::iterator it;
    for (it = this->_entities.begin(); it != this->_entities.end(); it++) {
      std::unique_ptr<T> &current = (*it);
      current->update(delta);
    }


//    std::vector<std::unique_ptr<ComponentHandler>>::iterator componentIterator;
//    for (componentIterator = this->_componentHandlers.begin(); componentIterator != this->_componentHandlers.end(); ++componentIterator) {
//      std::unique_ptr<ComponentHandler> &currentHandler = (*componentIterator);
//      currentHandler->update(this->_entities, delta);
//    }
  }

private:
  std::unique_ptr<T> _light;
  std::vector<std::unique_ptr<T> > _entities;
  std::vector<std::unique_ptr<ComponentHandler>> _componentHandlers;
};

#endif // WORLD_H
