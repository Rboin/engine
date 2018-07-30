#include "lightmesh.h"

LightMesh::LightMesh(GLuint vao, Vertex *v, Texture *t, Material *m) : Mesh(vao, v, t, m)
{

}

void LightMesh::initialize(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy)
{

//  proxy->glUseProgram(programId);
//  // Create VAO
//  proxy->glGenVertexArrays(1, &this->_vao);
//  proxy->glBindVertexArray(this->_vao);
//  this->_vertex->initialize(programId, proxy);
//  this->_texture->initialize(programId, proxy);
//  this->_material->initialize(programId, proxy);
//  proxy->glBindVertexArray(0);
//  this->_vertex->deleteBuffers(proxy);
//  proxy->glUseProgram(0);
}
