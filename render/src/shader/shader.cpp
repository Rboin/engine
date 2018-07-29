#include "shader.h"
#include <iostream>

Shader::Shader(ShaderInformation *shaderInformation)
{
  this->shaderInformation = std::unique_ptr<ShaderInformation>(shaderInformation);
}

void Shader::initialize(std::shared_ptr<OpenGLFunctionProxy> &proxy)
{
  this->initializeVertexShader(proxy);
  this->initializeFragmentShader(proxy);
}

GLuint Shader::getVertexShader()
{
  return this->vertexShader;
}

GLuint Shader::getFragmentShader()
{
  return this->fragmentShader;
}

void Shader::initializeVertexShader(std::shared_ptr<OpenGLFunctionProxy> &proxy)
{
  this->initializeShader(proxy,
                         this->shaderInformation->getVertexSource(),
                         this->vertexShader,
                         GL_VERTEX_SHADER);
}

void Shader::initializeFragmentShader(std::shared_ptr<OpenGLFunctionProxy> &proxy)
{
  this->initializeShader(proxy,
                         this->shaderInformation->getFragmentSource(),
                         this->fragmentShader,
                         GL_FRAGMENT_SHADER);
}

void Shader::initializeShader(std::shared_ptr<OpenGLFunctionProxy> &proxy,
                              std::string shaderSource,
                              GLuint &shader,
                              GLenum shaderType)
{
  const char *source = shaderSource.c_str();
  shader = proxy->glCreateShader(shaderType);
  proxy->glShaderSource(shader, 1, &source, nullptr);
  proxy->glCompileShader(shader);
  this->checkCompilationStatus(shader, shaderType, proxy);
}

void Shader::checkCompilationStatus(GLuint shader, GLenum type,
                                    std::shared_ptr<OpenGLFunctionProxy> &proxy)
{
  int status;
  proxy->glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  GLint blen = 0;
  GLsizei slen = 0;
  proxy->glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &blen);
  if(blen > 1) {
    GLchar *log = (GLchar *) malloc(blen);
    proxy->glGetShaderInfoLog(this->vertexShader, blen, &slen, log);
    std::string shaderType;
    if(shader == this->vertexShader) {
      shaderType = "VERTEX";
    } else if(shader == this->fragmentShader) {
      shaderType = "FRAGMENT";
    }
    std::cerr << "Shader compilation failed for:" << shaderType << "\n" << log << std::endl;
  }
}
