#pragma once

#include "Includes.h"

#import "GameObject.h"
#import "Transform.h"
#import "MeshRenderer.h"
#import "PillRotation.h"
#import "SnakeHead.h"

class GameManager
{
public:
    static void SceneSetup();
    static void UpdateGameObjects();
    static void FixedUpdateGameObjects();
    static void DrawGameObjects();
    static GameObject* AddGameObject();
    static void SetDirection(int dir, float& elapsedFrames);
private:
    static std::vector<GameObject*> objects;
    static SnakeHead* snake;
};

std::vector<GameObject*> GameManager::objects;
SnakeHead* GameManager::snake;

void GameManager::SceneSetup()
{
    // create objects n shit here
//    auto test = AddGameObject();
//    test->AddComponent(new SnakeHead());
//    test->GetComponent<GridComponent>()->UpdatePos();
//
//    auto test2 = AddGameObject();
//    test2->AddComponent(new SnakeHead());
//    test2->GetComponent<GridComponent>()->x = 10.0f;
//    test2->GetComponent<GridComponent>()->UpdatePos();
    
    auto test3 = AddGameObject();
    test3->AddComponent(new SnakeHead());
    test3->GetComponent<GridComponent>()->x = 10.0f;
    test3->GetComponent<GridComponent>()->y = 10.0f;
    test3->GetComponent<GridComponent>()->UpdatePos();
    GameManager::snake = test3->GetComponent<SnakeHead>();
    
//    auto test2 = AddGameObject();
//    test2->AddComponent(new Transform());
//    auto transform1 = test2->GetComponent<Transform>();
//    transform1->position = { -2.0f, 0.0f, -30.0f };
//    test2->AddComponent(new PillRotation());
//    Mesh *m1 = new Mesh("perc60.obj");
//    MeshRenderer *mr2 = new MeshRenderer();
//    mr2->SetColor({1.0f, 1.0f, 1.0f});
//    mr2->SetMesh(m1);
//    mr2->SetRenderer(new Renderer());
//    test2->AddComponent(mr2);
}

void GameManager::UpdateGameObjects()
{
    for (auto &go : objects)
    {
        go->UpdateComponents();
    }
}

void GameManager::FixedUpdateGameObjects()
{
    for (auto &go : objects)
    {
        go->FixedUpdateComponents();
    }
}

void GameManager::DrawGameObjects()
{
    for (auto &go : objects)
    {
        go->GetComponent<MeshRenderer>()->Draw();
    }
}

GameObject* GameManager::AddGameObject()
{
    GameObject *go = new GameObject();
    objects.push_back(go);
    return go;
}

void GameManager::SetDirection(int dir, float& elapsedFrames) {
    if((snake->dir + dir) % 2 == 1) {
        snake->dir = dir;
        elapsedFrames = 30.0f;
    }
}
