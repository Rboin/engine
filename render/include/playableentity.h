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

  void setPosition(glm::vec3 p);
  void setRotation(glm::vec3 r);
  void setScaling(glm::vec3 s);

  void update(const float &delta) override;
private:
  std::shared_ptr<Camera> _camera;
};

#endif // PLAYABLEENTITY_H
