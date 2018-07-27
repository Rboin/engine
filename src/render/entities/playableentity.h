#ifndef PLAYABLEENTITY_H
#define PLAYABLEENTITY_H

#include <memory>

#include "renderableentity.h"
#include "camera/camera.hpp"

class PlayableEntity : public RenderableEntity
{
public:
  PlayableEntity(Camera *c, Entity *e, RenderObject *r);

  std::shared_ptr<Camera> &getCamera();

  void update(const float &delta) override;
private:
  std::shared_ptr<Camera> _camera;
};

#endif // PLAYABLEENTITY_H
