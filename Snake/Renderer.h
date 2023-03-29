#pragma once

#include "Includes.h"

class Renderer
{
public:
    Renderer(const char *vertexShader, const char *fragmentShader, NSString *texName)
    {
        const char *vShaderPath = Utilities::FindPath(vertexShader);
        const char *fShaderPath = Utilities::FindPath(fragmentShader);
        char *vShaderStr = Utilities::ReadShaderFile(vShaderPath);
        char *fShaderStr = Utilities::ReadShaderFile(fShaderPath);
        this->program = Utilities::LoadProgram(vShaderStr, fShaderStr);
        Utilities::LoadTexture(texName);
    }
    
    void SetUniform(const std::string& uniformName)
    {
        auto location = glGetUniformLocation(program, uniformName.c_str());
        Utilities::PrintErrors("After glGetUniformLocation");
        locations.insert({ uniformName, location });
    }
    
    GLint& operator[](const char *str)
    {
        return locations.find(str)->second;
    }
    
    std::map<std::string, GLint> locations;
    GLuint program;
};
