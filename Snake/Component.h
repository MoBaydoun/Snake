#pragma once

#include "Mesh.h"
#include "Renderer.h"
#include "DrawCommands.h"

class Component
{
public:
    virtual ~Component() {}
    virtual void Awake() {}
    virtual void Update() {}
    
    void SetParent(GameObject* gameObject)
    {
        this->parent = gameObject;
    }
    
protected:
    GameObject *parent;
};

class Transform : public Component
{
public:
    GLKVector3 position, scale, rotation;
    
    void Awake() override
    {
        position = { 0.0f, 0.0f, 0.0f };
        scale = { 1.0f, 1.0f, 1.0f };
        rotation = { 0.0f, 0.0f, 0.0f };
    }
};

class MeshRenderer : public Component
{
public:
    void SetMesh(const Mesh *mesh)
    {
        this->mesh = mesh;
    }
    
    void SetRenderer(Renderer *renderer)
    {
        this->renderer = renderer;
    }
    
    void Awake() override
    {
        this->transform = parent->GetComponent<Transform>();
        Utilities::PrintErrors("After GetComponent Transform");
        renderer->SetUniform("mvp");
    }
    
    void Update() override
    {
        GLKMatrix4 model;
        model = GLKMatrix4TranslateWithVector3(GLKMatrix4Identity, this->transform->position);
        model = GLKMatrix4ScaleWithVector3(model, this->transform->scale);
        
        this->mvp = GLKMatrix4Multiply(GLKMatrix4Multiply(Camera::current->GetProjectionMatrix(), Camera::current->GetViewMatrix()), model);
    }
    
    void Draw()
    {
        Utilities::PrintErrors("Prior glUseProgram");
        glUseProgram(this->renderer->program);
        Utilities::PrintErrors("After glUseProgram");
        auto mvploc = this->renderer->locations.find("mvp")->second;
        glUniformMatrix4fv(mvploc, 1, FALSE, (const float *)this->mvp.m);
        Utilities::PrintErrors("After glUniformMatrix4fv");
        
        GLuint vao;
        glGenVertexArrays(1, &vao);
        Utilities::PrintErrors("After glGenVertexArrays");
        glBindVertexArray(vao);
        Utilities::PrintErrors("After glBindVertexArray");
        
        std::vector<GLuint> buffers;
        buffers.push_back(DrawCommands::PositionVBO(this->mesh->GetVertices().positions, this->renderer->program));
        buffers.push_back(DrawCommands::NormalVBO(this->mesh->GetVertices().normals, this->renderer->program));
        buffers.push_back(DrawCommands::TexCoordVBO(this->mesh->GetVertices().texCoords, this->renderer->program));
        if (this->mesh->GetVertices().colors.size() > 0) {
            buffers.push_back(DrawCommands::ColorVBO(this->mesh->GetVertices().colors, this->renderer->program));
        }
        buffers.push_back(DrawCommands::IndexVBO(this->mesh->GetIndices()));
        
        glDeleteBuffers((GLsizei)buffers.size(), &buffers[0]);
        Utilities::PrintErrors("After glDeleteBuffers");
        glDeleteVertexArrays(1, &vao);
        Utilities::PrintErrors("After glDeleteVertexArrays");
        
    }
    Renderer *renderer;
private:
    const Mesh *mesh;
    Transform *transform;
    GLKMatrix4 mvp;
};
