#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include <memory>
#include <glm/glm.hpp>
#include "mesh.h"
#include "texture.h"
#include "vertex.h"

typedef std::unique_ptr<Vertex> VertexPtr;
typedef std::unique_ptr<Texture> TexturePtr;

class RenderObject
{
public:
  RenderObject(Mesh *m);
  void initialize(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy);
  bool isInitialized() const;
  std::unique_ptr<Mesh> &getMesh();
  VertexPtr &getVertex();
  TexturePtr &getTexture();
  void render(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy, const glm::mat4 model, const glm::mat4 &viewProjectionMatrix);

private:
  bool initialized;
  std::unique_ptr<Mesh> _mesh;
};

#endif // RENDEROBJECT_H
