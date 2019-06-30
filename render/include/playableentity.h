#ifndef PLAYABLEENTITY_H
#define PLAYABLEENTITY_H

#include <memory>

#include "entity.h"
#include "camera.h"

class PlayableEntity : public Entity
{
public:
  PlayableEntity(std::shared_ptr<Camera> c);

  ~PlayableEntity();

  std::shared_ptr<Camera> &getCamera();

  void setPosition(glm::vec3 p);
  void setRotation(glm::vec3 r);
  void setScaling(glm::vec3 s);

//  void update(const double delta) override;
private:
  std::shared_ptr<Camera> _camera;
};

#endif // PLAYABLEENTITY_H
