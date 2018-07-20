#include "mesh.h"

Mesh::Mesh()
{
  Mesh(0, nullptr, nullptr, nullptr);
}

Mesh::Mesh(GLuint vao, Vertex *v, Texture *t, Material *m) : _initialized(false)
{
  this->_vao = vao;
  this->_vertex = std::unique_ptr<Vertex>(v);
  this->_texture = std::unique_ptr<Texture>(t);
  this->_material = std::unique_ptr<Material>(m);
}

void Mesh::initialize(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy)
{
  proxy->glUseProgram(programId);
  // Create VAO
  proxy->glGenVertexArrays(1, &this->_vao);
  proxy->glBindVertexArray(this->_vao);
  this->_vertex->initialize(programId, proxy);
  this->_texture->initialize(programId, proxy);
  this->_material->initialize(programId, proxy);
  proxy->glBindVertexArray(0);
  this->_vertex->deleteBuffers(proxy);
  proxy->glUseProgram(0);
}

bool Mesh::isInitialized()
{
  return this->_initialized;
}

void Mesh::setVao(GLuint vao)
{
  this->_vao = vao;
}

GLuint Mesh::getVao()
{
  return this->_vao;
}

void Mesh::setVertex(Vertex *v)
{
  this->_vertex = std::unique_ptr<Vertex>(v);
}

std::unique_ptr<Vertex> &Mesh::getVertex()
{
  return this->_vertex;
}

void Mesh::setTexture(Texture *t)
{
  this->_texture = std::unique_ptr<Texture>(t);
}

std::unique_ptr<Texture> &Mesh::getTexture()
{
  return this->_texture;
}

void Mesh::setMaterial(Material *m)
{
  this->_material = std::shared_ptr<Material>(m);
}

std::shared_ptr<Material> &Mesh::getMaterial()
{
  return this->_material;
}
