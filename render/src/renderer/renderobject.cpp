#include "renderobject.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

RenderObject::RenderObject(Mesh *m) : initialized(false)
{
  this->_mesh = std::unique_ptr<Mesh>(m);
}

void RenderObject::initialize(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy)
{
  if (!this->_mesh->isInitialized()) {
    this->_mesh->initialize(programId, proxy);
  }
}

bool RenderObject::isInitialized() const
{
  return this->initialized;
}

std::unique_ptr<Mesh> &RenderObject::getMesh()
{
  return this->_mesh;
}

VertexPtr &RenderObject::getVertex()
{
  return this->_mesh->getVertex();
}

TexturePtr &RenderObject::getTexture()
{
  return this->_mesh->getTexture();
}

static int tmpRads = 0;

void RenderObject::render(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy, const glm::mat4 model, const glm::mat4 &viewProjectionMatrix)
{
  // Bind texture(s).
  std::vector<std::unique_ptr<TextureImage>> &textures = this->_mesh->getTexture()->getTextures();
  for (unsigned int i = 0; i < textures.size(); i++) {
    std::unique_ptr<TextureImage> &currentTexture = textures.at(i);
    proxy->glActiveTexture(GL_TEXTURE0 + i);
    proxy->glBindTexture(GL_TEXTURE_2D, currentTexture->texture);
  }

  glm::mat4 MVP = viewProjectionMatrix * model;
  int transLoc = proxy->glGetUniformLocation(programId, "MVP");
  proxy->glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(MVP));

  // Bind VAO and draw elements using indices.
  GLuint vao = this->_mesh->getVao();
  unsigned int verticesSize = this->_mesh->getVertex()->getVerticesSize();
  proxy->glBindVertexArray(vao);
  proxy->glDrawArrays(GL_TRIANGLES, 0, verticesSize);
//  proxy->glDrawElements(GL_TRIANGLES, indiceSize, GL_UNSIGNED_INT, 0);
  proxy->glBindVertexArray(0);
}
