#include "renderer.h"

#include <vector>
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "renderobject.h"
#include "shaderinformation.h"

Renderer::Renderer() :
  _initialized(false),
  u_cameraPosition(-1)
{
}

Renderer::~Renderer()
{
  if (this->_proxy) {
//    this->_proxy->glDeleteProgram(this->_program);
  }
}

bool Renderer::hasFunctions()
{
  return this->_proxy != nullptr;
}

void Renderer::setFunctions(std::shared_ptr<OpenGLFunctionProxy> f)
{
  this->_proxy = f;
}

std::shared_ptr<OpenGLFunctionProxy> Renderer::getFunctionProxy()
{
  return this->_proxy;
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
  this->_proxy->glEnable(GL_BLEND);
  this->_proxy->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  this->_proxy->glEnable(GL_DEPTH_TEST);
  this->_proxy->glEnable(GL_LIGHTING);
  // COUNTER-CLOCKWISE FACE CULLING
  this->_proxy->glEnable(GL_CULL_FACE);
  this->_proxy->glCullFace(GL_BACK);
  this->_proxy->glFrontFace(GL_CCW);
  this->_proxy->glLinkProgram(this->_program);
  int status;
  this->_proxy->glGetProgramiv(this->_program, GL_LINK_STATUS, &status);
  if(!status) {
    char log[512];
    this->_proxy->glGetProgramInfoLog(this->_program, 512, nullptr, log);
    std::cerr << "Error while linking shader program(s):" << log << std::endl;
  }
  this->_proxy->glDetachShader(this->_program, vShader);
  this->_proxy->glDetachShader(this->_program, fShader);
  this->_proxy->glDeleteShader(vShader);
  this->_proxy->glDeleteShader(fShader);
}

void Renderer::addShader(Shader *shader)
{
  this->_shader = std::unique_ptr<Shader>(shader);
}

void Renderer::render(std::unique_ptr<Scene> &scene)
{

  if (this->_proxy) {
    if(!this->_initialized) {
      this->initialize();
      this->_initialized = true;
    }
    this->_proxy->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    this->_proxy->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    this->_proxy->glUseProgram(this->_program);

    if(this->u_cameraPosition < 0) {
      this->u_cameraPosition = this->_proxy->glGetUniformLocation(this->_program, "cameraPosition");
    }
    // Set camera position.
    glm::vec3 cameraPosition = scene->getCamera()->getPosition();
    this->_proxy->glUniform3fv(this->u_cameraPosition, 1, glm::value_ptr(cameraPosition));

    this->_currentViewProjection = scene->getCamera()->getProjectionMatrix() * scene->getCamera()->getViewMatrix();
    // Set light uniforms and render objects.
    this->renderLights(scene->getLights());
    // Render entities.
    this->renderEntities(scene->getWorld()->getEntities());
    this->_proxy->glUseProgram(0);
  }

}

void Renderer::renderEntities(std::vector<std::unique_ptr<Entity> > &entities)
{
  EntityVectorIterator iter;
  for(iter = entities.begin(); iter != entities.end(); ++iter) {
    std::unique_ptr<Entity> &entity = (*iter);
    this->renderEntity(entity);
  }
}

void Renderer::renderLights(std::vector<std::unique_ptr<Entity> > &lights)
{
  EntityVectorIterator iter;
  for(iter = lights.begin(); iter != lights.end(); ++iter) {
    std::unique_ptr<Entity> &entity = (*iter);
    this->renderEntity(entity);
  }

}

void Renderer::renderEntity(std::unique_ptr<Entity> &entity)
{
  std::shared_ptr<RenderComponent> renderComponent = entity->getComponents()->getComponent<RenderComponent>();
  std::shared_ptr<TransformComponent> transformComponent = entity->getComponents()->getComponent<TransformComponent>();
  std::shared_ptr<RenderObject> renderObject = renderComponent->getRenderObject();

  if (!renderObject->isInitialized()) {
    renderObject->initialize(this->_program, this->_proxy);
  }
  renderObject->render(this->_program, this->_proxy, transformComponent->getModel(), this->_currentViewProjection);
}

