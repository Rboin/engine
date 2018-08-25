#ifndef PLAYABLEENTITY_H
#define PLAYABLEENTITY_H

#include <memory>

#include "entity.hpp"
#include "camera.hpp"

class PlayableEntity : public Entity
{
public:
  PlayableEntity(std::shared_ptr<Camera> c);

  std::shared_ptr<Camera> &getCamera();

  void setPosition(glm::vec3 p);
  void setRotation(glm::vec3 r);
  void setScaling(glm::vec3 s);

  void update(const float &delta) override;
private:
  std::shared_ptr<Camera> _camera;
};

#endif // PLAYABLEENTITY_H
