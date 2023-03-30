#pragma once

#include "Includes.h"
#include "Component.h"
#include "Transform.h"

class PillRotation : public Component
{
public:
    void Awake() override;
    void Update() override;
private:
    Transform *t;
};

void PillRotation::Awake()
{
    t = parent->GetComponent<Transform>();
    t->rotation.z = 0.785398f;
}

void PillRotation::Update()
{
    t->rotation.y += 0.05f;
}
