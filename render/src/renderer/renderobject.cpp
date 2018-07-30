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

static int tmpRads = 0;

void RenderObject::render(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy, std::unique_ptr<Entity> &entity, const glm::mat4 &viewProjectionMatrix)
{

  // Bind VAO and draw elements using indices.
  GLuint vao = this->_mesh->getVao();
  this->bind(vao, proxy);
  // Bind texture(s).
  this->setTextures(proxy);

  this->_currentMVP = viewProjectionMatrix * entity->getModelMatrix();
  this->setUniforms(programId, proxy);
  unsigned int verticesSize = this->_mesh->getVertex()->getVerticesSize();
  proxy->glDrawArrays(GL_TRIANGLES, 0, verticesSize);
  this->unbind(proxy);
}

void RenderObject::setUniforms(GLuint program, std::shared_ptr<OpenGLFunctionProxy> &proxy)
{
  // Set MVP matrix.
  int mvpLocation = VertexAttribute::UNIFORM_MVP;
  proxy->glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(this->_currentMVP));
  // Set Color
  glm::vec3 color = this->_mesh->getMaterial()->getAmbientColor();
  int colorLocation = FragmentAttribute::UNIFORM_OBJECT_COLOR;
  proxy->glUniform3fv(colorLocation, 1, glm::value_ptr(color));
  // Set Color Power (light absorption)
  float power = this->_mesh->getMaterial()->getReflectPower();
  int powerLocation = FragmentAttribute::UNIFORM_REFLECTIVE_POWER;
  proxy->glUniform1fv(powerLocation, 1, &power);
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
