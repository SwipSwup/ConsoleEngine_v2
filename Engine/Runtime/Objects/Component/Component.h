//
// Created by david on 01/06/2024.
//

#ifndef CONSOLEENGINE_V2_COMPONENT_H
#define CONSOLEENGINE_V2_COMPONENT_H

namespace Engine
{

    class GameObject;
    struct Vector3D;
    class Component
    {
    protected:
        virtual ~Component();
        GameObject* root_ref;

        Vector3D* GetPosition();

    public:
        void
        SetRoot(GameObject* root);

    public:
        virtual void Tick(float deltaTime);
        virtual void FixTick();

        virtual void OnSpawn();

        virtual Component* Copy();
    };

} // Engine

#endif //CONSOLEENGINE_V2_COMPONENT_H
