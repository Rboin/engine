#include "lightrenderobject.h"

#include <glm/gtc/type_ptr.hpp>

LightRenderObject::LightRenderObject(Mesh *m) : RenderObject(m),
  u_position(-1),
  u_ambient(-1),
  u_diffuse(-1),
  u_specular(-1)
{

}

void LightRenderObject::initialize(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy)
{
  if (this->u_position < 0) {
    this->u_position = proxy->glGetUniformLocation(programId, "light.position");
  }
  if (this->u_ambient < 0) {
    this->u_ambient = proxy->glGetUniformLocation(programId, "light.ambient");
  }
  if (this->u_diffuse < 0) {
    this->u_diffuse = proxy->glGetUniformLocation(programId, "light.diffuse");
  }
  if (this->u_specular < 0) {
    this->u_specular = proxy->glGetUniformLocation(programId, "light.specular");
  }
  RenderObject::initialize(programId, proxy);
}

void LightRenderObject::render(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy, std::unique_ptr<Entity> &entity, const glm::mat4 &viewProjectionMatrix)
{
  GLuint vao = this->_mesh->getVao();
  this->bind(vao, proxy);

  this->updateMatrices(entity->getModelMatrix(), viewProjectionMatrix);
  this->_currentPosition = entity->getPosition();
  this->setUniforms(programId, proxy);
  unsigned int verticesSize = this->_mesh->getVertex()->getVerticesSize();
  proxy->glDrawArrays(GL_TRIANGLES, 0, verticesSize);
  this->unbind(proxy);
}

void LightRenderObject::setUniforms(GLuint program, std::shared_ptr<OpenGLFunctionProxy> &proxy)
{
  // Set Light uniform position
  proxy->glUniform3fv(this->u_position, 1, glm::value_ptr(this->_currentPosition));
  // Set Light uniform color
  proxy->glUniform3fv(this->u_ambient, 1, glm::value_ptr(this->_mesh->getMaterial()->getAmbientColor()));
//  proxy->glUniform3fv(this->u_diffuse, 1, glm::value_ptr(this->_mesh->getMaterial()->getDiffuseColor()));
  proxy->glUniform3fv(this->u_specular, 1, glm::value_ptr(this->_mesh->getMaterial()->getSpecularColor()));
  RenderObject::setUniforms(program, proxy);
}
