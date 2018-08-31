#include "lightrenderobject.h"

RenderObjects::Light::Light(Mesh *m) : BaseRenderObject(m),
  u_ambient(-1),
  u_diffuse(-1),
  u_specular(-1)
{

}
