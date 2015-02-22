#ifndef _SHADER_LOADER_
#define _SHADER_LOADER_

#include <vector>
#include <string>
#include <fstream>

#include <GL/glew.h>
#include <GL/wglew.h>
#include <GLFW\glfw3.h>

GLuint CreateShader(GLenum a_eShaderType, const char* a_strShaderFile);
GLuint CreateProgram(const char *a_vertex, const char *a_frag);

#endif