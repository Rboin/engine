#ifndef LIGHTMESH_H
#define LIGHTMESH_H

#include "mesh.h"

class LightMesh : public Mesh
{
public:
  LightMesh(GLuint vao, Vertex *v, Material* m);


  // Mesh interface
public:
  void initialize(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy) override;
};

#endif // LIGHTMESH_H
