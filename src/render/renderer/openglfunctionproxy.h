#ifndef OPENGLFUNCTIONOBJECT_H
#define OPENGLFUNCTIONOBJECT_H

#include "GL/gl.h"

class OpenGLFunctionProxy
{
public:
  virtual ~OpenGLFunctionProxy() {}
  // Program
  virtual GLuint glCreateProgram() = 0;
  virtual void glDeleteProgram(GLuint program) = 0;
  virtual void glLinkProgram(GLuint program) = 0;
  virtual void glUseProgram(GLuint program) = 0;
  virtual void glGetProgramiv(GLuint program, GLenum pname, GLint *params) = 0;
  virtual void glGetProgramInfoLog(GLuint program, GLsizei maxLength, GLsizei *length, GLchar *infoLog) = 0;
  // Shader
  virtual GLuint glCreateShader(GLenum type) = 0;
  virtual void glAttachShader(GLuint program, GLuint shader) = 0;
  virtual void glShaderSource(GLuint shader, GLsizei count, const GLchar *const *string, const GLint *length) = 0;
  virtual void glCompileShader(GLuint shader) = 0;
  virtual void glDeleteShader(GLuint shader) = 0;
  virtual void glGetShaderiv(GLuint shader, GLenum pname, GLint *params) = 0;
  virtual void glGetShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei *length, GLchar *infoLog) = 0;
  // Texture
  virtual void glGenTextures(GLsizei n, GLuint *textures) = 0;
  virtual void glBindTexture(GLenum target, GLuint texture) = 0;
  virtual void glTexParameteri(GLenum target, GLenum pname, GLint param) = 0;
  virtual void glTexParameterfv(GLenum target, GLenum pname, const GLfloat *params) = 0;
  virtual void glTexImage2D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels) = 0;
  virtual void glActiveTexture(GLenum unit) = 0;
  virtual void glGenerateMipMap(GLenum target) = 0;
  virtual void glPixelStorei(GLenum pname, GLint param) = 0;
  // Buffer
  virtual void glGenVertexArrays(GLsizei n, GLuint *arrays) = 0;
  virtual void glDeleteVertexArrays(GLsizei n, const GLuint *arrays) = 0;
  virtual void glBindVertexArray(GLuint array) = 0;
  virtual void glGenBuffers(GLsizei n, GLuint *buffers) = 0;
  virtual void glBindBuffer(GLenum target, GLuint buffer) = 0;
  virtual void glBufferData(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage) = 0;
  virtual void glDeleteBuffers(GLsizei n, const GLuint *buffers) = 0;
  virtual void glSwapBuffers() = 0;
  virtual void glEnableVertexAttribArray(GLuint index) = 0;
  virtual void glDisableVertexAttribArray(GLuint index) = 0;
  virtual void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer) = 0;
  virtual void glBindAttribLocation(GLuint program, GLuint index, const GLchar *name) = 0;
  virtual GLint glGetAttribLocation(GLuint program, const GLchar *name) = 0;
  virtual GLint glGetUniformLocation(GLuint program, const GLchar *name) = 0;
  virtual void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) = 0;
  virtual void glUniform1i(GLint location, GLint v0) = 0;
  // Drawing
  virtual void glDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices) = 0;
  virtual void glDrawArrays(GLenum mode, GLint first, GLsizei count) = 0;
  virtual void glClear(GLbitfield mask) = 0;
  virtual void glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) = 0;
  // Misc
  virtual void glEnable(GLenum cap) = 0;
  virtual void glBlendFunc(GLenum sfactor, GLenum dfactor) = 0;
  virtual const GLubyte *glGetString(GLenum name) = 0;
  virtual void glViewport(GLint x, GLint y, GLsizei width, GLsizei height) = 0;

};

#endif // OPENGLFUNCTIONOBJECT_H
