//
// Created by david on 01/06/2024.
//

#include "Component.h"
#include "../GameObject.h"

namespace Engine
{
    Engine::Component::~Component()
    {
    }

    void Engine::Component::SetRoot(GameObject* root)
    {
        this->root_ref = root;
    }

    void Engine::Component::Tick(float deltaTime)
    {
    }

    void Engine::Component::FixTick()
    {
    }

    void Engine::Component::OnSpawn()
    {
    }

    Vector3D* Component::GetPosition()
    {
        return root_ref->position;
    }

    Component* Component::Clone()
    {
        Component* newComponent = new Component();
        newComponent->SetComponentData(this);
        return newComponent;
    }

    void Component::SetComponentData(Component* reference)
    {
        root_ref = reference->root_ref;
    }
} // Engine