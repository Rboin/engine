#ifndef SHADER_H
#define SHADER_H


#include <memory>

#include "shaderinformation.h"
#include "renderer/openglfunctionproxy.h"

class Shader
{
public:
  Shader(ShaderInformation *information);
  void initialize(std::shared_ptr<OpenGLFunctionProxy> &proxy);

  GLuint getVertexShader();
  GLuint getFragmentShader();
private:
  GLuint vertexShader, fragmentShader;
  std::unique_ptr<ShaderInformation> shaderInformation;

  void initializeVertexShader(std::shared_ptr<OpenGLFunctionProxy> &proxy);
  void initializeFragmentShader(std::shared_ptr<OpenGLFunctionProxy> &proxy);
  void initializeShader(std::shared_ptr<OpenGLFunctionProxy> &proxy, std::string shaderSource, GLuint &shader, GLenum shaderType);
  void checkCompilationStatus(GLuint shader, GLenum type, std::shared_ptr<OpenGLFunctionProxy> &proxy);
};

#endif // SHADER_H
