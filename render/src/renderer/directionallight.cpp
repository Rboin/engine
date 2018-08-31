#include "directionallight.h"

#include <glm/gtc/type_ptr.hpp>

RenderObjects::DirectionalLight::DirectionalLight(Mesh *m) : Light(m),
  u_direction(-1)
{

}

void RenderObjects::DirectionalLight::initialize(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy)
{
  if (this->u_direction < 0) {
    this->u_direction = proxy->glGetUniformLocation(programId, "directionalLight.direction");
  }
  if (this->u_ambient < 0) {
    this->u_ambient = proxy->glGetUniformLocation(programId, "directionalLight.ambient");
  }
  if (this->u_diffuse < 0) {
    this->u_diffuse = proxy->glGetUniformLocation(programId, "directionalLight.diffuse");
  }
  if (this->u_specular < 0) {
    this->u_specular = proxy->glGetUniformLocation(programId, "directionalLight.specular");
  }
  BaseRenderObject::initialize(programId, proxy);
}

void RenderObjects::DirectionalLight::render(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy, const glm::mat4 &modelMatrix, const glm::mat4 &viewProjectionMatrix)
{
  GLuint vao = this->_mesh->getVao();
  this->bind(vao, proxy);
  this->setTextures(proxy);

  this->updateMatrices(modelMatrix, viewProjectionMatrix);

  glm::vec3 direction(modelMatrix[3]);
  this->_direction = glm::vec4(direction, 0.0f);
  this->setUniforms(programId, proxy);
  unsigned int verticesSize = this->_mesh->getVertex()->getVerticesSize();
  proxy->glDrawArrays(GL_TRIANGLES, 0, verticesSize);
  this->unbind(proxy);
}

void RenderObjects::DirectionalLight::setUniforms(GLuint program, std::shared_ptr<OpenGLFunctionProxy> &proxy)
{
  // Set Light uniform position
  proxy->glUniform3fv(this->u_direction, 1, glm::value_ptr(this->_direction));
  // Set Light uniform color
  proxy->glUniform3fv(this->u_ambient, 1, glm::value_ptr(this->_mesh->getMaterial()->getAmbientColor()));
  proxy->glUniform3fv(this->u_diffuse, 1, glm::value_ptr(this->_mesh->getMaterial()->getDiffuseColor()));
  proxy->glUniform3fv(this->u_specular, 1, glm::value_ptr(this->_mesh->getMaterial()->getSpecularColor()));
  BaseRenderObject::setUniforms(program, proxy);
}
