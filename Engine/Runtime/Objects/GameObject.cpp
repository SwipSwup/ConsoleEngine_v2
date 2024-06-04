//
// Created by david on 01/06/2024.
//

#include <typeinfo>
#include <iostream>
#include "GameObject.h"
#include "../Utility/Vector/Vector3D.h"
#include "Component/Component.h"

namespace Engine
{
    GameObject::GameObject(Scene* root)
    {
        scene_ref = root;

        position = new Vector3D(0, 0, 0);
    }

    GameObject::GameObject(char* name)
    {
        this->name = name;

        position = new Vector3D(0, 0, 0);
    }

    GameObject::GameObject()
    {
        position = new Vector3D(0, 0, 0);
    }

    GameObject::GameObject(GameObject* gameObject)
    {
        position = gameObject->position;
        //TODO find solution to create new instances of component
        for (Component* item: gameObject->GetComponents()) {
            components.push_back(item->Clone());
        }

        name = gameObject->name;
    }

    Scene* GameObject::GetScene()
    {
        return scene_ref;
    }

    void GameObject::SetScene(Scene* scene)
    {
        this->scene_ref = scene;
    }

    /*Vector3D* GameObject::GetPosition()
    {
        return position;
    }

    void GameObject::SetPosition(Vector3D position)
    {
        delete this->position;
        this->position = new Vector3D(position);
    }*/

    void GameObject::TickComponents(float deltaTime)
    {
        for (Component* component : components)
        {

            component->Tick(deltaTime);
        }
    }

    void GameObject::FixTickComponents()
    {
        for (Component* component : components)
        {
            component->FixTick();
        }
    }

    void GameObject::Tick(float deltaTime)
    {
        TickComponents(deltaTime);
    }

    void GameObject::FixTick()
    {
        FixTickComponents();
    }

    void GameObject::OnSpawn()
    {

        for (Component* component : components)
        {
            component->SetRoot(this);
            component->OnSpawn();
        }
    }

    GameObject* GameObject::Clone(GameObject* gameObject)
    {
        return new GameObject(gameObject);
    }

    const std::list<Component*> GameObject::GetComponents() const
    {
        return components;
    }


} // Engine