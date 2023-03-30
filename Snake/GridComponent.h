#pragma once

#include "Includes.h"
#include "Component.h"
#include "Transform.h"

class GridComponent : public Component {
public:
    void Awake() override;
    void UpdatePos();
    float x = 0, y = 0;
private:
    Transform *t;
};

void GridComponent::Awake() {
    parent->AddComponent(new Transform());
    t = parent->GetComponent<Transform>();
    t->position.z = -60.0f;
}

void GridComponent::UpdatePos() {
    t->position.x = (x - 10) * 2;
    t->position.y = (y - 10) * -2;
}
