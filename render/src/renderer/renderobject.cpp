#include "renderobject.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

RenderObject::RenderObject(Mesh *m) :
  initialized(false),
  u_normalModel(-1),
  u_modelToWorld(-1),
  u_modelToProjection(-1)
{
  this->_mesh = std::unique_ptr<Mesh>(m);
}

void RenderObject::initialize(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy)
{
  if (!this->_mesh->isInitialized()) {
    this->_mesh->initialize(programId, proxy);
  }
  if (this->u_normalModel < 0) {
    this->u_normalModel = proxy->glGetUniformLocation(programId, "normalModel");
  }
  if (this->u_modelToWorld < 0) {
    this->u_modelToWorld = proxy->glGetUniformLocation(programId, "modelToWorld");
  }
  if (this->u_modelToProjection < 0) {
    this->u_modelToProjection = proxy->glGetUniformLocation(programId, "modelToProjection");
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

void RenderObject::render(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy, Entity &entity, const glm::mat4 &viewProjectionMatrix)
{
  // Bind VAO and draw elements using indices.
  GLuint vao = this->_mesh->getVao();
  this->bind(vao, proxy);
  // Bind texture(s).
  this->setTextures(proxy);

  this->updateMatrices(entity.getModelMatrix(), viewProjectionMatrix);
  this->setUniforms(programId, proxy);
  unsigned int verticesSize = this->_mesh->getVertex()->getVerticesSize();
  proxy->glDrawArrays(GL_TRIANGLES, 0, verticesSize);
  this->unbind(proxy);
}

void RenderObject::setUniforms(GLuint program, std::shared_ptr<OpenGLFunctionProxy> &proxy)
{
  // Set matrices (normal -> lightDirection, model -> world and model -> projection)
  proxy->glUniformMatrix3fv(this->u_normalModel, 1, GL_FALSE, glm::value_ptr(this->_normalModel));
  proxy->glUniformMatrix4fv(this->u_modelToWorld, 1, GL_FALSE, glm::value_ptr(this->_modelToWorld));
  proxy->glUniformMatrix4fv(this->u_modelToProjection, 1, GL_FALSE, glm::value_ptr(this->_modelToProjection));
  // Set Colors
//  proxy->glUniform3fv(this->_mesh->getMaterial()->getUniformAmbient(), 1, glm::value_ptr(this->_mesh->getMaterial()->getAmbientColor()));
//  proxy->glUniform3fv(this->_mesh->getMaterial()->getUniformDiffuse(), 1, glm::value_ptr(this->_mesh->getMaterial()->getDiffuseColor()));
//  proxy->glUniform3fv(this->_mesh->getMaterial()->getUniformSpecular(), 1, glm::value_ptr(this->_mesh->getMaterial()->getSpecularColor()));
  // Set Shine Power (light reflection strength)
  float power = this->_mesh->getMaterial()->getShinePower();
  proxy->glUniform1fv(this->_mesh->getMaterial()->getUniformShininess(), 1, &power);
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
  std::unique_ptr<Texture> &texture = this->_mesh->getMaterial()->getTexture();
  proxy->glUniform1i(texture->getUniformDiffuse(), 0);
  proxy->glActiveTexture(GL_TEXTURE0);
  proxy->glBindTexture(GL_TEXTURE_2D, texture->getDiffuseTexture()->texture);
  proxy->glUniform1i(texture->getUniformSpecular(), 1);
  proxy->glActiveTexture(GL_TEXTURE1);
  proxy->glBindTexture(GL_TEXTURE_2D, texture->getSpecularTexture()->texture);
  proxy->glUniform1i(texture->getUniformEmission(), 2);
  proxy->glActiveTexture(GL_TEXTURE2);
  proxy->glBindTexture(GL_TEXTURE_2D, texture->getEmissionTexture()->texture);

//  for (unsigned int i = 0; i < textures.size(); i++) {
//    std::unique_ptr<TextureImage> &currentTexture = textures.at(i);
//    proxy->glActiveTexture(GL_TEXTURE0 + i);
//    proxy->glBindTexture(GL_TEXTURE_2D, currentTexture->texture);
//  }
}

void RenderObject::updateMatrices(const glm::mat4 &model, const glm::mat4 &viewProjection)
{
  this->_normalModel = glm::mat3(glm::transpose(glm::inverse(model)));
  this->_modelToWorld = model;
  this->_modelToProjection = viewProjection * model;
}
