#pragma once

#include "Entity.h"
#include "Game.h"

class Test : Entity
{
public:
    Test(const vec3f& position);
protected:
    void Create(const vec3f& position) override;
    void Update(float elapsedTime) override;
private:
    vec3f position;
};
