#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <memory>
#include <algorithm>


#include "glm/gtc/matrix_transform.hpp"
#include "glm/glm.hpp"

template<class T>
class World
{
public:
  World()
  {
    this->entities = std::vector<std::unique_ptr<T> >();
  }

  void initialize() {}

  void addEntity(T *entity)
  {
    this->entities.push_back(std::unique_ptr<T>(entity));
  }

  void removeEntity(T *entity)
  {
    this->entities.erase(
      std::remove_if(
        this->entities.begin(),
        this->entities.end(),
    [&] (std::unique_ptr<T> &e) {
      return entity == e.get();
    }),
    this->entities.end()
    );
  }

  const std::vector<std::unique_ptr<T>> &getEntities() const
  {
    return this->entities;
  }

  void update(const double &delta)
  {
    typename std::vector<std::unique_ptr<T>>::iterator it;
    for (it = this->entities.begin(); it != this->entities.end(); it++) {
      (*it).get()->update(delta);
    }
  }

private:
  std::vector<std::unique_ptr<T> > entities;
};

#endif // WORLD_H
