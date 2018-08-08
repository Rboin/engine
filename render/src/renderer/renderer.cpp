#include "renderer.h"

#include <vector>
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "renderobject.h"
#include "shaderinformation.h"

Renderer::Renderer(std::shared_ptr<Camera> &c) :
  _initialized(false),
  u_cameraPosition(-1)
{
  this->_camera = c;
}

Renderer::~Renderer()
{
  if (this->_proxy) {
    this->_proxy->glDeleteProgram(this->_program);
  }
}

bool Renderer::hasFunctions()
{
  return this->_proxy != nullptr;
}

void Renderer::setFunctions(std::shared_ptr<OpenGLFunctionProxy> &f)
{
  this->_proxy = f;
}

void Renderer::initialize()
{
  // Create shader program and link shaders.
  this->_program = this->_proxy->glCreateProgram();
  this->_proxy->glUseProgram(this->_program);
  // Initialize the Vertex and Fragment shaders.
  this->_shader->initialize(this->_proxy);
  GLuint vShader = this->_shader->getVertexShader();
  GLuint fShader = this->_shader->getFragmentShader();
  this->_proxy->glAttachShader(this->_program, vShader);
  this->_proxy->glAttachShader(this->_program, fShader);
  this->_proxy->glLinkProgram(this->_program);
  this->_proxy->glEnable(GL_BLEND);
  this->_proxy->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  this->_proxy->glEnable(GL_DEPTH_TEST);
  this->_proxy->glEnable(GL_LIGHTING);
//  this->_proxy->glEnable(GL_CULL_FACE);
//  this->_proxy->glCullFace(GL_FRONT);
  int status;
  this->_proxy->glGetProgramiv(this->_program, GL_LINK_STATUS, &status);
  if(!status) {
    char log[512];
    this->_proxy->glGetProgramInfoLog(this->_program, 512, nullptr, log);
    std::cerr << "Error while linking shader program(s):" << log << std::endl;
  }
  this->_proxy->glDeleteShader(vShader);
  this->_proxy->glDeleteShader(fShader);
}

void Renderer::initializeRenderObjects(std::unique_ptr<World<RenderableEntity> > &world)
{
  // Get all entities
  RenderableVector &renderables = world->getEntities();
  RenderableVectorIterator it;
  // Initialize renderobjects in a loop.
  for(it = renderables.begin(); it != renderables.end(); it++) {
    std::unique_ptr<RenderObject> &currentRenderObject = (*it)->getRenderObject();
    if (!currentRenderObject->isInitialized()) {
      currentRenderObject->initialize(this->_program, this->_proxy);
    }
  }

}

void Renderer::addShader(Shader *shader)
{
  this->_shader = std::unique_ptr<Shader>(shader);
}

void Renderer::render(std::unique_ptr<World<RenderableEntity> > &world)
{
  if (this->_proxy) {
    if(!this->_initialized) {
      this->initialize();
      this->initializeRenderObjects(world);

      this->_initialized = true;
    }
    this->_proxy->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    this->_proxy->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    this->_proxy->glUseProgram(this->_program);

    if(this->u_cameraPosition < 0) {
      this->u_cameraPosition = this->_proxy->glGetUniformLocation(this->_program, "cameraPosition");
    }

    glm::vec3 cameraPosition = this->_camera->getPosition();
    this->_proxy->glUniform3fv(this->u_cameraPosition, 1, glm::value_ptr(cameraPosition));
    glm::mat4 viewProjection = this->_camera->getProjectionMatrix() * this->_camera->getViewMatrix();
    const std::vector<std::unique_ptr<RenderableEntity>> &v = world->getEntities();
    std::vector<std::unique_ptr<RenderableEntity>>::const_iterator iter;
    for(iter = v.begin(); iter != v.end(); ++iter) {
      const std::unique_ptr<RenderableEntity> &entity = (*iter);
      entity->render(this->_program, this->_proxy, viewProjection);
    }
    this->_proxy->glUseProgram(0);
  }

}

std::shared_ptr<Camera> &Renderer::getCamera()
{
  return this->_camera;
}
