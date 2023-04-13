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
    std::deque<GameObject*> body;
    bool justExpanded = false;
private:
    bool isMoving = true;
};

void SnakeHead::Awake() {
    parent->AddComponent(new GridComponent());
    gc = parent->GetComponent<GridComponent>();
    gc->t->rotation = {M_PI / 2.0f, M_PI, 0.0f};
    
    Mesh *m = new Mesh("head.obj");
    MeshRenderer *mr = new MeshRenderer();
    mr->SetColor({0.23f, 1.0f, 0.11f});
    mr->SetMesh(m);
    mr->SetRenderer(new Renderer());
    parent->AddComponent(mr);
}

void SnakeHead::FixedUpdate() {
    if(justExpanded) {
        body.back()->GetComponent<Transform>()->scale = {1.0f, 1.0f, 1.0f};
    }
    else if(!body.empty()) {
        auto tail = body.front();
        auto tgc = body.front()->GetComponent<GridComponent>();
        tgc->x = gc->x;
        tgc->y = gc->y;
        tgc->UpdatePos();
        body.pop_front();
        body.push_back(tail);
    }
    
    
    
    if(isMoving) {
        switch(dir) {
            case 0: // right
                ++gc->x;
                gc->t->rotation = {M_PI / 2.0f, 3 * M_PI / 2, 0.0f};
                break;
            case 2: // left
                --gc->x;
                gc->t->rotation = {M_PI / 2.0f, M_PI / 2, 0.0f};
                break;
            case 1: // down
                ++gc->y;
                gc->t->rotation = {M_PI / 2.0f, M_PI, 0.0f};
                break;
            case 3: // up
                --gc->y;
                gc->t->rotation = {M_PI / 2.0f, 0, 0.0f};
                break;
        }
    }
    
    if(!body.empty()) {
        auto tc = body.front()->GetComponent<GridComponent>();
        auto tn = body.size() > 1 ? body[1]->GetComponent<GridComponent>() : gc;
        
        if(tc->x != tn->x) {
            tc->t->rotation.y = M_PI / 2.0f * (tc->x - tn->x);
        } else {
            tc->t->rotation.y = M_PI / 2.0f + M_PI / 2.0f * (tn->y - tc->y);
        }
        
        body.front()->GetComponent<MeshRenderer>()->SetMesh(new Mesh("tail.obj"));
        body.front()->GetComponent<MeshRenderer>()->Awake();
    }
    
    if(body.size() > 1) {
//        auto bbc = body[body.size() - 2]->GetComponent<GridComponent>();
//
//        Mesh *nm = new Mesh(gc->x != bbc->x && gc->y != bbc->y ? "turnleft.obj" : "body.obj");
        Mesh *nm = new Mesh("Cube.obj");
        body.back()->GetComponent<MeshRenderer>()->SetMesh(nm);
        body.back()->GetComponent<MeshRenderer>()->Awake();
//
//        auto bt = body.back()->GetComponent<Transform>();
//        if((gc->x < bbc->x && gc->y < bbc->y) || (gc->x > bbc->x && gc->y > bbc->y)) {
//            bt->rotation.y = -M_PI / 2.0f;
//        }
//        else if((gc->x < bbc->x && gc->y > bbc->y) || (gc->x > bbc->x && gc->y < bbc->y)) {
//            bt->rotation.y = M_PI / 2.0f;
//        }
    }
    
    justExpanded = false;
    
    gc->UpdatePos();
}
