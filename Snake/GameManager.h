#pragma once

#include "Includes.h"

#import "GameObject.h"
#import "Transform.h"
#import "MeshRenderer.h"

class GameManager
{
public:
    static void SceneSetup();
    static void UpdateGameObjects();
    static void FixedUpdateGameObjects();
    static void DrawGameObjects();
    static GameObject* AddGameObject();
private:
    static std::vector<GameObject*> objects;
};

std::vector<GameObject*> GameManager::objects;

void GameManager::SceneSetup()
{
    // create objects n shit here
    auto test = AddGameObject();
    test->AddComponent(new Transform());
    Mesh *m = new Mesh("Cube.obj");
    MeshRenderer *mr = new MeshRenderer();
    mr->SetColor({0.23f, 1.0f, 0.11f});
    mr->SetMesh(m);
    mr->SetRenderer(new Renderer());
    test->AddComponent(mr);
    
    auto test2 = AddGameObject();
    test2->AddComponent(new Transform());
    auto transform = test2->GetComponent<Transform>();
    transform->position = { -2.0f, 1.0f, 0.0f };
    transform->scale = { 0.5f, 1.0f, 1.0f };
    Mesh *m1 = new Mesh("Cube.obj");
    MeshRenderer *mr2 = new MeshRenderer();
    mr2->SetColor({0.23f, 1.0f, 0.11f});
    mr2->SetMesh(m1);
    mr2->SetRenderer(new Renderer());
    test2->AddComponent(mr2);
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
