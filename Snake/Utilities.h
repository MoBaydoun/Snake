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

template <typename T>
struct Vector3
{
    T x, y, z;
    Vector3(T x, T y, T z) : x(x), y(y), z(z) {};
};

typedef Vector3<GLfloat> vec3f;
typedef Vector3<GLuint> vec3i;
