#pragma once

#include "Includes.h"
#include "Component.h"
#include "GridComponent.h"

enum Direction { right, up, left, down };

class SnakeHead : public Component {
public:
    void Awake() override;
    void FixedUpdate() override;
    int dir = 1;
    GridComponent *gc;
    std::queue<GameObject*> body;
    bool justExpanded = false;
private:
    bool isMoving = true;
};

void SnakeHead::Awake() {
    parent->AddComponent(new GridComponent());
    gc = parent->GetComponent<GridComponent>();
    
    Mesh *m = new Mesh("Cube.obj");
    MeshRenderer *mr = new MeshRenderer();
    mr->SetColor({0.23f, 1.0f, 0.11f});
    mr->SetMesh(m);
    mr->SetRenderer(new Renderer());
    parent->AddComponent(mr);
}

void SnakeHead::FixedUpdate() {
    if(!justExpanded && !body.empty()) {
        auto tail = body.front();
        auto tgc = body.front()->GetComponent<GridComponent>();
        tgc->x = gc->x;
        tgc->y = gc->y;
        tgc->UpdatePos();
        body.pop();
        body.push(tail);
    }
    
    if(isMoving) {
        switch(dir) {
            case 0:
                ++gc->x;
                break;
            case 2:
                --gc->x;
                break;
            case 1:
                ++gc->y;
                break;
            case 3:
                --gc->y;
                break;
        }
    }
    
    justExpanded = false;
    
    gc->UpdatePos();
}
