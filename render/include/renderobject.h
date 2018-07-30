#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include <memory>
#include <glm/glm.hpp>
#include "mesh.h"
#include "texture.h"
#include "vertex.h"
#include "entity.h"

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
  virtual void render(GLuint programId,
                      std::shared_ptr<OpenGLFunctionProxy> &proxy,
                      std::unique_ptr<Entity> &entity,
                      const glm::mat4 &viewProjectionMatrix);
  virtual void setUniforms(GLuint program, std::shared_ptr<OpenGLFunctionProxy> &proxy);

protected:
  bool initialized;
  glm::mat4 _currentMVP;
  std::unique_ptr<Mesh> _mesh;

  void bind(GLuint vao, std::shared_ptr<OpenGLFunctionProxy> &proxy);
  void unbind(std::shared_ptr<OpenGLFunctionProxy> &proxy);
  void setTextures(std::shared_ptr<OpenGLFunctionProxy> &proxy);
};

#endif // RENDEROBJECT_H
