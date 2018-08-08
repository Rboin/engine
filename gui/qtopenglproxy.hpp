#ifndef QTOPENGLPROXY_HPP
#define QTOPENGLPROXY_HPP

#include <memory>

#include "openglfunctionproxy.h"

template<class T>
class QtOpenGLProxy : public OpenGLFunctionProxy
{
public:
  QtOpenGLProxy(T *functions)
  {
    this->_functions = std::unique_ptr<T>(functions);
  }

  ~QtOpenGLProxy() override {}

private:
  std::unique_ptr<T> _functions;

  // OpenGLFunctionProxy interface
public:
  GLuint glCreateProgram() override
  {
    return this->_functions->glCreateProgram();
  }

  void glDeleteProgram(GLuint program) override
  {
    this->_functions->glDeleteProgram(program);
  }

  void glLinkProgram(GLuint program) override
  {
    this->_functions->glLinkProgram(program);
  }

  void glUseProgram(GLuint program) override
  {
    this->_functions->glUseProgram(program);
  }

  void glGetProgramiv(GLuint program, GLenum pname, GLint *params) override
  {
    this->_functions->glGetProgramiv(program, pname, params);
  }

  void glGetProgramInfoLog(GLuint program, GLsizei maxLength, GLsizei *length, GLchar *infoLog) override
  {
    this->_functions->glGetProgramInfoLog(program, maxLength, length, infoLog);
  }

  GLuint glCreateShader(GLenum type) override
  {
    return this->_functions->glCreateShader(type);
  }

  void glAttachShader(GLuint program, GLuint shader) override
  {
    this->_functions->glAttachShader(program, shader);
  }

  void glShaderSource(GLuint shader, GLsizei count, const GLchar * const *string, const GLint *length) override
  {
    this->_functions->glShaderSource(shader, count, string, length);
  }

  void glCompileShader(GLuint shader) override
  {

    this->_functions->glCompileShader(shader);
  }

  void glDeleteShader(GLuint shader) override
  {
    this->_functions->glDeleteShader(shader);
  }

  void glGetShaderiv(GLuint shader, GLenum pname, GLint *params) override
  {
    this->_functions->glGetShaderiv(shader, pname, params);
  }

  void glGetShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei *length, GLchar *infoLog) override
  {
    this->_functions->glGetShaderInfoLog(shader, maxLength, length, infoLog);
  }

  void glGenTextures(GLsizei n, GLuint *textures) override
  {
    this->_functions->glGenTextures(n, textures);
  }

  void glBindTexture(GLenum target, GLuint texture) override
  {
    this->_functions->glBindTexture(target, texture);
  }

  void glTexParameteri(GLenum target, GLenum pname, GLint param) override
  {
    this->_functions->glTexParameteri(target, pname, param);
  }

  void glTexParameterfv(GLenum target, GLenum pname, const GLfloat *params) override
  {
    this->_functions->glTexParameterfv(target, pname, params);
  }

  void glTexImage2D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels) override
  {
    this->_functions->glTexImage2D(target, level, internalFormat, width, height, border, format, type, pixels);
  }

  void glActiveTexture(GLenum unit) override
  {
    this->_functions->glActiveTexture(unit);
  }

  void glGenerateMipMap(GLenum target) override
  {
    this->_functions->glGenerateMipmap(target);
  }

  void glPixelStorei(GLenum pname, GLint param) override
  {
    this->_functions->glPixelStorei(pname, param);
  }

  void glGenVertexArrays(GLsizei n, GLuint *arrays) override
  {
    this->_functions->glGenVertexArrays(n, arrays);
  }

  void glDeleteVertexArrays(GLsizei n, const GLuint *arrays) override
  {
    this->_functions->glDeleteVertexArrays(n, arrays);
  }

  void glBindVertexArray(GLuint array) override
  {
    this->_functions->glBindVertexArray(array);
  }

  void glGenBuffers(GLsizei n, GLuint *buffers) override
  {
    this->_functions->glGenBuffers(n, buffers);
  }

  void glBindBuffer(GLenum target, GLuint buffer) override
  {
    this->_functions->glBindBuffer(target, buffer);
  }

  void glBufferData(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage) override
  {
    this->_functions->glBufferData(target, size, data, usage);
  }

  void glDeleteBuffers(GLsizei n, const GLuint *buffers) override
  {
    this->_functions->glDeleteBuffers(n, buffers);
  }

  void glSwapBuffers() override {}

  void glEnableVertexAttribArray(GLuint index) override
  {
    this->_functions->glEnableVertexAttribArray(index);
  }

  void glDisableVertexAttribArray(GLuint index) override
  {
    this->_functions->glDisableVertexAttribArray(index);
  }

  void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer) override
  {
    this->_functions->glVertexAttribPointer(index, size, type, normalized, stride, pointer);
  }

  void glBindAttribLocation(GLuint program, GLuint index, const GLchar *name) override
  {
    this->_functions->glBindAttribLocation(program, index, name);
  }

  GLint glGetAttribLocation(GLuint program, const GLchar *name) override
  {
    return this->_functions->glGetAttribLocation(program, name);
  }

  GLint glGetUniformLocation(GLuint program, const GLchar *name) override
  {
    return this->_functions->glGetUniformLocation(program, name);
  }

  void glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) override
  {
    this->_functions->glUniformMatrix3fv(location, count, transpose, value);
  }

  void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) override
  {
    this->_functions->glUniformMatrix4fv(location, count, transpose, value);
  }

  void glUniform1fv(GLint location, GLsizei count, const GLfloat *value) override
  {
    this->_functions->glUniform1fv(location, count, value);
  }

  void glUniform3fv(GLint location, GLsizei count, const GLfloat *value) override
  {
    this->_functions->glUniform3fv(location, count, value);
  }

  void glUniform4fv(GLint location, GLsizei count, const GLfloat *value) override
  {
    this->_functions->glUniform4fv(location, count, value);
  }

  void glUniform1i(GLint location, GLint v0) override
  {
    this->_functions->glUniform1i(location, v0);
  }

  void glDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices) override
  {
    this->_functions->glDrawElements(mode, count, type, indices);
  }

  void glDrawArrays(GLenum mode, GLint first, GLsizei count) override
  {
    this->_functions->glDrawArrays(mode, first, count);
  }

  void glClear(GLbitfield mask) override
  {
    this->_functions->glClear(mask);
  }

  void glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) override
  {
    this->_functions->glClearColor(red, green, blue, alpha);
  }

  void glEnable(GLenum cap) override
  {
    this->_functions->glEnable(cap);
  }

  void glBlendFunc(GLenum sfactor, GLenum dfactor) override
  {
    this->_functions->glBlendFunc(sfactor, dfactor);
  }

  void glCullFace(GLenum mode) override
  {
    this->_functions->glCullFace(mode);
  }

  void glFrontFace(GLenum mode) override
  {
    this->_functions->glFrontFace(mode);
  }

  const GLubyte *glGetString(GLenum name) override
  {
    return this->_functions->glGetString(name);
  }

  void glViewport(GLint x, GLint y, GLsizei width, GLsizei height) override
  {
    this->_functions->glViewport(x, y, width, height);
  }
};

#endif // QTOPENGLPROXY_HPP
