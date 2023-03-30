#pragma once

#include "Includes.h"
#include "Mesh.h"
#include "Renderer.h"
#include "Component.h"

class MeshRenderer : public Component
{
public:
    
    void SetColor(GLKVector3 color)
    {
        this->color = color;
    }
    
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
        renderer->SetUniform("model");
        renderer->SetUniform("view");
        renderer->SetUniform("projection");
        renderer->SetUniform("objectColor");
        renderer->SetUniform("lightColor");
        renderer->SetUniform("lightPosition");
        renderer->SetUniform("cameraPosition");
        
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        
        buffers.push_back(DrawCommands::PositionVBO(mesh->GetVertices().positions, renderer->program));
        buffers.push_back(DrawCommands::NormalVBO(mesh->GetVertices().normals, renderer->program));
//        buffers.push_back(DrawCommands::TexCoordVBO(mesh->GetVertices().texCoords, renderer->program));
        buffers.push_back(DrawCommands::IndexVBO(mesh->GetIndices()));
    }
    
    void Update() override
    {
        model = GLKMatrix4TranslateWithVector3(GLKMatrix4Identity, transform->position);
        model = GLKMatrix4ScaleWithVector3(model, transform->scale);
        model = GLKMatrix4RotateWithVector3(model, transform->radians, transform->rotation);
    }
    
    void Draw()
    {
        Utilities::PrintErrors("Prior glUseProgram");
        glUseProgram(this->renderer->program);
        Utilities::PrintErrors("After glUseProgram");
        glUniformMatrix4fv((*renderer)["model"], 1, FALSE, (const float *) model.m);
        glUniformMatrix4fv((*renderer)["view"], 1, FALSE, (const float *) Camera::current->GetViewMatrix().m);
        glUniformMatrix4fv((*renderer)["projection"], 1, FALSE, (const float *) Camera::current->GetProjectionMatrix().m);
        Utilities::PrintErrors("After glUniformMatrix4fv");
        glUniform3f((*renderer)["objectColor"], color.x, color.y, color.z);
        glUniform3f((*renderer)["lightColor"], 1.0f, 1.0f, 1.0f);
        glUniform3f((*renderer)["lightPosition"], 0.0f, 0.0f, 2.0f);
        auto cameraPosition = Camera::current->GetPosition();
        glUniform3f((*renderer)["cameraPosition"], cameraPosition.x, cameraPosition.y, cameraPosition.z);
        
        glBindVertexArray(vao);
    
        glDrawElements(GL_TRIANGLES, (GLsizei)mesh->GetIndices().size(), GL_UNSIGNED_INT, 0);
        
        glBindVertexArray(0);
        
    }
    Renderer *renderer;
private:
    const Mesh *mesh;
    Transform *transform;
    GLKMatrix4 model;
    GLuint vao;
    std::vector<GLuint> buffers;
    GLKVector3 color;
};

