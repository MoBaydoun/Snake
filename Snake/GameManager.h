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
    static int score;
private:
    static std::vector<GameObject*> objects;
    static SnakeHead* snake;
    static GridComponent* pill;
    static float GetRandomCoord();
    static void CollisionChecker();
};

std::vector<GameObject*> GameManager::objects;
SnakeHead* GameManager::snake;
GridComponent* GameManager::pill;

int GameManager::score = 0;

void GameManager::SceneSetup()
{
    auto snake = AddGameObject();
    snake->AddComponent(new SnakeHead());
    snake->GetComponent<GridComponent>()->x = 10.0f;
    snake->GetComponent<GridComponent>()->y = 10.0f;
    snake->GetComponent<GridComponent>()->UpdatePos();
    GameManager::snake = snake->GetComponent<SnakeHead>();
    
    auto pill = AddGameObject();
    pill->AddComponent(new GridComponent());
    auto pgc = pill->GetComponent<GridComponent>();
    pgc->x = GetRandomCoord();
    pgc->y = GetRandomCoord();
    pgc->UpdatePos();
    pill->AddComponent(new PillRotation());
    Mesh *m1 = new Mesh("perc60.obj");
    MeshRenderer *mr2 = new MeshRenderer();
    mr2->SetColor({1.0f, 1.0f, 1.0f});
    mr2->SetMesh(m1);
    mr2->SetRenderer(new Renderer());
    pill->AddComponent(mr2);
    GameManager::pill = pgc;
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
    GameManager::CollisionChecker();
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

void GameManager::CollisionChecker() {
    if(snake->gc->x == pill->x && snake->gc->y == pill->y) {
        ++score;
        pill->x = GetRandomCoord();
        pill->y = GetRandomCoord();
        pill->UpdatePos();
    }
}

float GameManager::GetRandomCoord() {
    return (float) (std::rand() % 21);
}
