#ifndef MESH_H
#define MESH_H

#include <memory>
#include <GL/gl.h>

#include "material.h"
#include "texture.h"
#include "vertex.h"

class Mesh
{
public:
  Mesh();
  Mesh(GLuint vao, Vertex *v, Texture *t, Material* m);

  virtual void initialize(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy);
  bool isInitialized();
  void setVao(GLuint vao);
  GLuint getVao();
  void setVertex(Vertex *v);
  std::unique_ptr<Vertex> &getVertex();
  void setTexture(Texture *t);
  std::unique_ptr<Texture> &getTexture();
  void setMaterial(Material *m);
  std::shared_ptr<Material> &getMaterial();
private:
  bool _initialized;
  GLuint _vao;
  std::unique_ptr<Vertex> _vertex;
  std::unique_ptr<Texture> _texture;
  std::shared_ptr<Material> _material;
};

#endif // MESH_H
