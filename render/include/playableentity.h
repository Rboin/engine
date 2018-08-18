#ifndef PLAYABLEENTITY_H
#define PLAYABLEENTITY_H

#include <memory>

#include "renderableentity.h"
#include "camera.hpp"

class PlayableEntity : public RenderableEntity
{
public:
  PlayableEntity(std::shared_ptr<Camera> c, RenderObject *r);

  std::shared_ptr<Camera> &getCamera();

  void update(const float &delta) override;
private:
  std::shared_ptr<Camera> _camera;

  // Entity interface
public:
  void setPosition(glm::vec3 p) override;
  void setRotation(glm::vec3 r) override;
};

#endif // PLAYABLEENTITY_H
