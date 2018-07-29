#ifndef LIGHT_H
#define LIGHT_H

#include "renderableentity.h"

class Light : public RenderableEntity
{
public:
  Light(Entity *e, RenderObject *r);
};

#endif // LIGHT_H
