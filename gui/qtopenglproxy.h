#ifndef QTOPENGLPROXY_H
#define QTOPENGLPROXY_H

#include <memory>
#include <QOpenGLFunctions_4_3_Core>
#include "openglfunctionproxy.h"

class QtOpenGLProxy : public OpenGLFunctionProxy
{
public:
  QtOpenGLProxy(QOpenGLFunctions_4_3_Core *functions);
  ~QtOpenGLProxy() override;

private:
  std::unique_ptr<QOpenGLFunctions_4_3_Core> _functions;

  // OpenGLFunctionProxy interface
public:
  GLuint glCreateProgram() override;
  void glDeleteProgram(GLuint program) override;
  void glLinkProgram(GLuint program) override;
  void glUseProgram(GLuint program) override;
  void glGetProgramiv(GLuint program, GLenum pname, GLint *params) override;
  void glGetProgramInfoLog(GLuint program, GLsizei maxLength, GLsizei *length, GLchar *infoLog) override;
  GLuint glCreateShader(GLenum type) override;
  void glAttachShader(GLuint program, GLuint shader) override;
  void glShaderSource(GLuint shader, GLsizei count, const GLchar * const *string, const GLint *length) override;
  void glCompileShader(GLuint shader) override;
  void glDeleteShader(GLuint shader) override;
  void glGetShaderiv(GLuint shader, GLenum pname, GLint *params) override;
  void glGetShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei *length, GLchar *infoLog) override;
  void glGenTextures(GLsizei n, GLuint *textures) override;
  void glBindTexture(GLenum target, GLuint texture) override;
  void glTexParameteri(GLenum target, GLenum pname, GLint param) override;
  void glTexParameterfv(GLenum target, GLenum pname, const GLfloat *params) override;
  void glTexImage2D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels) override;
  void glActiveTexture(GLenum unit) override;
  void glGenerateMipMap(GLenum target) override;
  void glPixelStorei(GLenum pname, GLint param) override;
  void glGenVertexArrays(GLsizei n, GLuint *arrays) override;
  void glDeleteVertexArrays(GLsizei n, const GLuint *arrays) override;
  void glBindVertexArray(GLuint array) override;
  void glGenBuffers(GLsizei n, GLuint *buffers) override;
  void glBindBuffer(GLenum target, GLuint buffer) override;
  void glBufferData(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage) override;
  void glDeleteBuffers(GLsizei n, const GLuint *buffers) override;
  void glSwapBuffers() override;
  void glEnableVertexAttribArray(GLuint index) override;
  void glDisableVertexAttribArray(GLuint index) override;
  void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer) override;
  void glBindAttribLocation(GLuint program, GLuint index, const GLchar *name) override;
  GLint glGetAttribLocation(GLuint program, const GLchar *name) override;
  GLint glGetUniformLocation(GLuint program, const GLchar *name) override;
  void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) override;
  void glUniform1fv(GLint location, GLsizei count, const GLfloat *value) override;
  void glUniform3fv(GLint location, GLsizei count, const GLfloat *value) override;
  void glUniform4fv(GLint location, GLsizei count, const GLfloat *value) override;
  void glUniform1i(GLint location, GLint v0) override;
  void glDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices) override;
  void glDrawArrays(GLenum mode, GLint first, GLsizei count) override;
  void glClear(GLbitfield mask) override;
  void glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) override;
  void glEnable(GLenum cap) override;
  void glBlendFunc(GLenum sfactor, GLenum dfactor) override;
  const GLubyte *glGetString(GLenum name) override;
  void glViewport(GLint x, GLint y, GLsizei width, GLsizei height) override;
};

#endif // QTOPENGLPROXY_H
