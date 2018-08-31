#ifndef LIGHTRENDEROBJECT_H
#define LIGHTRENDEROBJECT_H

#include "renderobject.h"

namespace RenderObjects
{

class Light : public BaseRenderObject
{
public:
  Light(Mesh *m);
protected:
  int u_ambient, u_diffuse, u_specular;
};
}

#endif // LIGHTRENDEROBJECT_H
