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

//TODO: Change BaseRenderObject to RenderComponent
//TODO: Change Renderer to RenderSystem, move drawing logic ((un-)bind, setTextures, updateMatrices, render and setUniforms) to RenderSystem
// RenderComponent should only hold textures, vertices, and uniforms

namespace RenderObjects
{
class BaseRenderObject
{
public:
  BaseRenderObject(Mesh *m);
  virtual void initialize(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy);
  bool isInitialized() const;
  std::unique_ptr<Mesh> &getMesh();
  VertexPtr &getVertex();
  TexturePtr &getTexture();
  virtual void render(GLuint programId,
                      std::shared_ptr<OpenGLFunctionProxy> &proxy,
                      const glm::mat4 &modelMatrix,
                      const glm::mat4 &viewProjectionMatrix);
  virtual void setUniforms(GLuint program, std::shared_ptr<OpenGLFunctionProxy> &proxy);

protected:
  bool initialized;
  int u_normalModel, u_modelToWorld, u_modelToProjection;
  glm::mat3 _normalModel;
  glm::mat4 _modelToWorld, _modelToProjection;
  std::unique_ptr<Mesh> _mesh;

  void bind(GLuint vao, std::shared_ptr<OpenGLFunctionProxy> &proxy);
  void unbind(std::shared_ptr<OpenGLFunctionProxy> &proxy);
  void setTextures(std::shared_ptr<OpenGLFunctionProxy> &proxy);
  void updateMatrices(const glm::mat4 &model, const glm::mat4 &viewProjection);
};
}

#endif // RENDEROBJECT_H
