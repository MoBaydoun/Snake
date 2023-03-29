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
        transform = parent->GetComponent<Transform>();
        Utilities::PrintErrors("After GetComponent Transform");
        renderer->SetUniform("mvp");
        
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        
        buffers.push_back(DrawCommands::PositionVBO(mesh->GetVertices().positions, renderer->program));
        buffers.push_back(DrawCommands::NormalVBO(mesh->GetVertices().normals, renderer->program));
        buffers.push_back(DrawCommands::TexCoordVBO(mesh->GetVertices().texCoords, renderer->program));
        if (mesh->GetVertices().colors.size() > 0) {
            buffers.push_back(DrawCommands::ColorVBO(mesh->GetVertices().colors, renderer->program));
        }
        buffers.push_back(DrawCommands::IndexVBO(mesh->GetIndices()));
    }
    
    void Update() override
    {
        GLKMatrix4 model;
        model = GLKMatrix4TranslateWithVector3(GLKMatrix4Identity, transform->position);
        model = GLKMatrix4ScaleWithVector3(model, transform->scale);
        
        this->mvp = GLKMatrix4Multiply(GLKMatrix4Multiply(Camera::current->GetProjectionMatrix(), Camera::current->GetViewMatrix()), model);
    }
    
    void Draw()
    {
        Utilities::PrintErrors("Prior glUseProgram");
        glUseProgram(this->renderer->program);
        Utilities::PrintErrors("After glUseProgram");
        glUniformMatrix4fv((*renderer)["mvp"], 1, FALSE, (const float *) mvp.m);
        Utilities::PrintErrors("After glUniformMatrix4fv");
        
        glBindVertexArray(vao);
    
        glDrawElements(GL_TRIANGLES, (GLsizei)mesh->GetIndices().size(), GL_UNSIGNED_INT, 0);
        
        glBindVertexArray(0);
        
    }
    Renderer *renderer;
private:
    const Mesh *mesh;
    Transform *transform;
    GLKMatrix4 mvp;
    GLuint vao;
    std::vector<GLuint> buffers;
};
