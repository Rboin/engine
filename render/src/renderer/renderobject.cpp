#include "renderobject.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaderattribute.h"

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

void RenderObject::render(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy, std::unique_ptr<Entity> &entity, const glm::mat4 &viewProjectionMatrix)
{
  // Bind VAO and draw elements using indices.
  GLuint vao = this->_mesh->getVao();
  this->bind(vao, proxy);
  // Bind texture(s).
  this->setTextures(proxy);

  this->updateMatrices(entity->getModelMatrix(), viewProjectionMatrix);
  this->setUniforms(programId, proxy);
  unsigned int verticesSize = this->_mesh->getVertex()->getVerticesSize();
  proxy->glDrawArrays(GL_TRIANGLES, 0, verticesSize);
  this->unbind(proxy);
}

void RenderObject::setUniforms(GLuint program, std::shared_ptr<OpenGLFunctionProxy> &proxy)
{
  // Set matrices (normal -> lightDirection, model -> world and model -> projection)
  proxy->glUniformMatrix3fv(VertexAttribute::UNIFORM_MODEL_NORMAL, 1, GL_FALSE, glm::value_ptr(this->_normalModel));
  proxy->glUniformMatrix4fv(VertexAttribute::UNIFORM_MODEL_WORLD, 1, GL_FALSE, glm::value_ptr(this->_modelToWorld));
  proxy->glUniformMatrix4fv(VertexAttribute::UNIFORM_MODEL_PROJECTION, 1, GL_FALSE, glm::value_ptr(this->_modelToProjection));
  // Set Color
  glm::vec3 color = this->_mesh->getMaterial()->getAmbientColor();
  proxy->glUniform3fv(FragmentAttribute::UNIFORM_OBJECT_COLOR, 1, glm::value_ptr(color));
  // Set Color Power (light absorption)
  float power = this->_mesh->getMaterial()->getReflectPower();
  proxy->glUniform1fv(FragmentAttribute::UNIFORM_REFLECTIVE_POWER, 1, &power);
  // Set Shine Power (light reflection strength)
  power = this->_mesh->getMaterial()->getShinePower();
  proxy->glUniform1fv(FragmentAttribute::UNIFORM_SHINE_POWER, 1, &power);
}

void RenderObject::bind(GLuint vao, std::shared_ptr<OpenGLFunctionProxy> &proxy)
{
  proxy->glBindVertexArray(vao);
}

void RenderObject::unbind(std::shared_ptr<OpenGLFunctionProxy> &proxy)
{
  proxy->glBindVertexArray(0);
}

void RenderObject::setTextures(std::shared_ptr<OpenGLFunctionProxy> &proxy)
{
  std::vector<std::unique_ptr<TextureImage>> &textures = this->_mesh->getTexture()->getTextures();
  for (unsigned int i = 0; i < textures.size(); i++) {
    std::unique_ptr<TextureImage> &currentTexture = textures.at(i);
    proxy->glActiveTexture(GL_TEXTURE0 + i);
    proxy->glBindTexture(GL_TEXTURE_2D, currentTexture->texture);
  }
}

void RenderObject::updateMatrices(const glm::mat4 &model, const glm::mat4 &viewProjection)
{
  this->_normalModel = glm::mat3(glm::transpose(glm::inverse(model)));
  this->_modelToWorld = model;
  this->_modelToProjection = viewProjection * model;
}
