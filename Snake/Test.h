#pragma once

#include "Entity.h"

class Test : Entity
{
public:
    Test(const vec3f& position);
protected:
    void Create(const vec3f& position) override;
    void Update() override;
};
