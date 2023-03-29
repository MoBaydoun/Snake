#pragma once

#include "Includes.h"

class Utilities
{
public:
    static char *ReadShaderFile(const char *fileName);
    static GLuint LoadShader(GLenum type, const char *shaderFile);
    static GLuint LoadProgram(const char *vertexSrc, const char *fragmentSrc);
    static const char* FindPath(const char *fileName);
    static void PrintErrors(const char *location);
    static void LoadTexture(NSString *fileName);
private:
    Utilities() {}
};
