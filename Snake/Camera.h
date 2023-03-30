#pragma once

#include "Includes.h"

class Camera
{
public:
    static Camera *current;
    Camera(GLKVector3 position, GLKVector3 target, GLfloat fov, GLfloat aspectRatio, GLfloat nearClipping, GLfloat farClipping) : position(position), target(target), fov(fov), aspectRatio(aspectRatio), nearClipping(nearClipping), farClipping(farClipping)
    {
        UpdateViewMatrix();
        UpdateProjectionMatrix();
    }
    
    void SetPosition(GLKVector3 position)
    {
        this->position = position;
        UpdateViewMatrix();
    }
    
    const GLKVector3& GetPosition() const
    {
        return position;
    }
    
    void SetTarget(GLKVector3 target)
    {
        this->target = target;
        UpdateViewMatrix();
    }
    
    void SetAspectRatio(GLfloat aspectRatio)
    {
        this->aspectRatio = aspectRatio;
        UpdateProjectionMatrix();
    }
    
    const GLKMatrix4& GetViewMatrix() const { return this->view; }
    const GLKMatrix4& GetProjectionMatrix() const { return this->projection; }
    
    static GLKVector3 MoveTowards(GLKVector3 currentPosition, GLKVector3 targetPosition, float maxDistance) {
        GLKVector3 direction = GLKVector3Subtract(targetPosition, currentPosition);
        float distance = GLKVector3Length(direction);
        if (distance <= maxDistance || distance == 0.0f) {
            return currentPosition;
        }
        GLKVector3 result = GLKVector3Add(currentPosition, GLKVector3MultiplyScalar(GLKVector3Normalize(direction), maxDistance));
        return result;
    }
    
private:
    GLKVector3 position, target;
    GLfloat fov, aspectRatio, nearClipping, farClipping;
    GLKMatrix4 view, projection;
    
    void UpdateViewMatrix()
    {
        this->view = GLKMatrix4MakeLookAt(this->position.x, this->position.y, this->position.z, this->target.x, this->target.y, this->target.z, 0.0f, 1.0f, 0.0f);
    }
    
    void UpdateProjectionMatrix()
    {
        this->projection = GLKMatrix4MakePerspective(fov, aspectRatio, nearClipping, farClipping);
    }
};
