#pragma once

#include "Includes.h"

class Renderer
{
public:
    Renderer(const char *vertexShader, const char *fragmentShader)
    {
        const char *vShaderPath = Utilities::FindPath(vertexShader);
        const char *fShaderPath = Utilities::FindPath(fragmentShader);
        char *vShaderStr = Utilities::ReadShaderFile(vShaderPath);
        char *fShaderStr = Utilities::ReadShaderFile(fShaderPath);
        this->program = Utilities::LoadProgram(vShaderStr, fShaderStr);
        std::cout << "Renderer created." << std::endl;
    }
    
    void SetUniform(const std::string& uniformName)
    {
        auto location = glGetUniformLocation(program, uniformName.c_str());
        Utilities::PrintErrors("After glGetUniformLocation");
        locations.insert({ uniformName, location });
    }
    
    std::map<std::string, GLint> locations;
    GLuint program;
};
