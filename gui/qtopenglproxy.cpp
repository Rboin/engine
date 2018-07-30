#include "qtopenglproxy.h"

QtOpenGLProxy::QtOpenGLProxy(QOpenGLFunctions_4_3_Core *functions)
{
  this->_functions = std::unique_ptr<QOpenGLFunctions_4_3_Core>(functions);
}

QtOpenGLProxy::~QtOpenGLProxy()
{
}

GLuint QtOpenGLProxy::glCreateProgram()
{
  return this->_functions->glCreateProgram();
}

void QtOpenGLProxy::glDeleteProgram(GLuint program)
{
  this->_functions->glDeleteProgram(program);
}

GLuint QtOpenGLProxy::glCreateShader(GLenum type)
{
  return this->_functions->glCreateShader(type);
}

void QtOpenGLProxy::glUseProgram(GLuint program)
{
  this->_functions->glUseProgram(program);
}

void QtOpenGLProxy::glLinkProgram(GLuint program)
{
  this->_functions->glLinkProgram(program);
}

void QtOpenGLProxy::glShaderSource(GLuint shader, GLsizei count, const GLchar *const *string, const GLint *length)
{
  this->_functions->glShaderSource(shader, count, string, length);
}

void QtOpenGLProxy::glCompileShader(GLuint shader)
{
  this->_functions->glCompileShader(shader);
}

void QtOpenGLProxy::glAttachShader(GLuint program, GLuint shader)
{
  this->_functions->glAttachShader(program, shader);
}

void QtOpenGLProxy::glGenVertexArrays(GLsizei n, GLuint *arrays)
{
  this->_functions->glGenVertexArrays(n, arrays);
}

void QtOpenGLProxy::glDeleteVertexArrays(GLsizei n, const GLuint *arrays)
{
  this->_functions->glDeleteVertexArrays(n, arrays);
}

void QtOpenGLProxy::glBindVertexArray(GLuint array)
{
  this->_functions->glBindVertexArray(array);
}

void QtOpenGLProxy::glGenBuffers(GLsizei n, GLuint *buffers)
{
  this->_functions->glGenBuffers(n, buffers);
}

void QtOpenGLProxy::glBindBuffer(GLenum target, GLuint buffer)
{
  this->_functions->glBindBuffer(target, buffer);
}

void QtOpenGLProxy::glBufferData(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage)
{
  this->_functions->glBufferData(target, size, data, usage);
}

void QtOpenGLProxy::glDeleteBuffers(GLsizei n, const GLuint *buffers)
{
  this->_functions->glDeleteBuffers(n, buffers);
}

const GLubyte *QtOpenGLProxy::glGetString(GLenum name)
{
  return this->_functions->glGetString(name);
}

void QtOpenGLProxy::glSwapBuffers()
{
}

GLint QtOpenGLProxy::glGetAttribLocation(GLuint program, const GLchar *name)
{
  return this->_functions->glGetAttribLocation(program, name);
}

GLint QtOpenGLProxy::glGetUniformLocation(GLuint program, const GLchar *name)
{
  return this->_functions->glGetUniformLocation(program, name);
}

void QtOpenGLProxy::glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
  this->_functions->glUniformMatrix4fv(location, count, transpose, value);
}

void QtOpenGLProxy::glUniform1fv(GLint location, GLsizei count, const GLfloat *value)
{
  this->_functions->glUniform1fv(location, count, value);
}

void QtOpenGLProxy::glUniform3fv(GLint location, GLsizei count, const GLfloat *value)
{
  this->_functions->glUniform3fv(location, count, value);
}

void QtOpenGLProxy::glUniform4fv(GLint location, GLsizei count, const GLfloat *value)
{
  this->_functions->glUniform4fv(location, count, value);
}

void QtOpenGLProxy::glUniform1i(GLint location, GLint v0)
{
  this->_functions->glUniform1i(location, v0);
}

void QtOpenGLProxy::glDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices)
{
  this->_functions->glDrawElements(mode, count, type, indices);
}

void QtOpenGLProxy::glClear(GLbitfield mask)
{
  this->_functions->glClear(mask);
}

void QtOpenGLProxy::glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
  this->_functions->glClearColor(red, green, blue, alpha);
}

void QtOpenGLProxy::glEnable(GLenum cap)
{
  this->_functions->glEnable(cap);
}

void QtOpenGLProxy::glBlendFunc(GLenum sfactor, GLenum dfactor)
{
  this->_functions->glBlendFunc(sfactor, dfactor);
}

void QtOpenGLProxy::glBindAttribLocation(GLuint program, GLuint index, const GLchar *name)
{
  this->_functions->glBindAttribLocation(program, index, name);
}

void QtOpenGLProxy::glGetShaderiv(GLuint shader, GLenum pname, GLint *params)
{
  this->_functions->glGetShaderiv(shader, pname, params);
}

void QtOpenGLProxy::glGetShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei *length, GLchar *infoLog)
{
  this->_functions->glGetShaderInfoLog(shader, maxLength, length, infoLog);
}

void QtOpenGLProxy::glGenTextures(GLsizei n, GLuint *textures)
{
  this->_functions->glGenTextures(n, textures);
}

void QtOpenGLProxy::glBindTexture(GLenum target, GLuint texture)
{
  this->_functions->glBindTexture(target, texture);
}

void QtOpenGLProxy::glTexParameteri(GLenum target, GLenum pname, GLint param)
{
  this->_functions->glTexParameteri(target, pname, param);
}

void QtOpenGLProxy::glTexParameterfv(GLenum target, GLenum pname, const GLfloat *params)
{
  this->_functions->glTexParameterfv(target, pname, params);
}

void QtOpenGLProxy::glTexImage2D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels)
{
  this->_functions->glTexImage2D(target, level, internalFormat, width, height, border, format, type, pixels);
}

void QtOpenGLProxy::glActiveTexture(GLenum unit)
{
  this->_functions->glActiveTexture(unit);
}

void QtOpenGLProxy::glGenerateMipMap(GLenum target)
{
  this->_functions->glGenerateMipmap(target);
}

void QtOpenGLProxy::glPixelStorei(GLenum pname, GLint param)
{
  this->_functions->glPixelStorei(pname, param);
}

void QtOpenGLProxy::glViewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
  this->_functions->glViewport(x, y, width, height);
}

void QtOpenGLProxy::glGetProgramiv(GLuint program, GLenum pname, GLint *params)
{
  this->_functions->glGetProgramiv(program, pname, params);
}

void QtOpenGLProxy::glGetProgramInfoLog(GLuint program, GLsizei maxLength, GLsizei *length, GLchar *infoLog)
{
  this->_functions->glGetProgramInfoLog(program, maxLength, length, infoLog);
}

void QtOpenGLProxy::glDeleteShader(GLuint shader)
{
  this->_functions->glDeleteShader(shader);
}

void QtOpenGLProxy::glEnableVertexAttribArray(GLuint index)
{
  this->_functions->glEnableVertexAttribArray(index);
}

void QtOpenGLProxy::glDisableVertexAttribArray(GLuint index)
{
  this->_functions->glDisableVertexAttribArray(index);
}

void QtOpenGLProxy::glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer)
{
  this->_functions->glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

void QtOpenGLProxy::glDrawArrays(GLenum mode, GLint first, GLsizei count)
{
  this->_functions->glDrawArrays(mode, first, count);
}
