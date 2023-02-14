#pragma once

#include "Includes.h"

class Utilities
{
public:
    static char *ReadShaderFile(const char *fileName);
    static GLuint LoadShader(GLenum type, const char *shaderFile);
    static GLuint LoadProgram(const char *vertexSrc, const char *fragmentSrc);
private:
    Utilities() {}
};
