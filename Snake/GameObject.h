#pragma once

#include "Includes.h"

class Component;

class GameObject
{
public:
    template <typename T>
    void AddComponent(T* component);
    
    template <typename T>
    T* GetComponent() const;
    
    void UpdateComponents() const;
private:
    std::map<std::type_index, Component*> components;
};

#include "Component.h"

template <typename T>
void GameObject::AddComponent(T* component)
{
    if (components.count(typeid(T)) > 0) return;
    component->SetParent(this);
    component->Awake();
    components.insert({ typeid(T), component });
}

template <typename T>
T* GameObject::GetComponent() const
{
    auto it = components.find(typeid(T));
    if (it != components.end())
    {
        Utilities::PrintErrors("During GetComponent");
        return static_cast<T*>(it->second);
    }
    return nullptr;
}

void GameObject::UpdateComponents() const
{
    for (auto &c : components)
    {
        c.second->Update();
    }
}
