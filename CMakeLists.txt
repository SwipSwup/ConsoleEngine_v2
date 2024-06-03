cmake_minimum_required(VERSION 3.28)
project(ConsoleEngine_v2)

include_directories(${PROJECT_SOURCE_DIR}/Engine)

set(CMAKE_CXX_STANDARD 17)

add_executable(ConsoleEngine_v2 main.cpp
        Engine/ConsoleEngine.cpp
        Engine/ConsoleEngine.h
        Engine/Core/Window/Window.cpp
        Engine/Core/Window/Window.h
        Engine/Core/Scene/Scene.cpp
        Engine/Core/Scene/Scene.h
        Engine/Runtime/Objects/GameObject.cpp
        Engine/Runtime/Objects/GameObject.h
        Engine/Runtime/Objects/Component/Component.cpp
        Engine/Runtime/Objects/Component/Component.h
        Engine/Core/RenderSystem/Renderer.cpp
        Engine/Core/RenderSystem/Renderer.h
        Engine/Runtime/Utility/Vector/Vector2D.cpp
        Engine/Runtime/Utility/Vector/Vector2D.h
        Engine/Runtime/Utility/Vector/Vector3D.cpp
        Engine/Runtime/Utility/Vector/Vector3D.h
        Engine/Runtime/Utility/Color/Color.cpp
        Engine/Runtime/Utility/Color/Color.h
        Engine/Runtime/Utility/Sprite/Sprite.cpp
        Engine/Runtime/Utility/Sprite/Sprite.h
        Engine/Core/Scene/SceneManager.cpp
        Engine/Core/Scene/SceneManager.h
        Engine/Runtime/Objects/Component/DefaultComponents/Rendering/CameraComponent.cpp
        Engine/Runtime/Objects/Component/DefaultComponents/Rendering/CameraComponent.h
        Engine/Runtime/Objects/Component/DefaultComponents/Rendering/SpriteRenderComponent.cpp
        Engine/Runtime/Objects/Component/DefaultComponents/Rendering/SpriteRenderComponent.h
        Engine/Core/InputSystem/InputSystem.cpp
        Engine/Core/InputSystem/InputSystem.h
        Game/Player/CameraController.cpp
        Game/Player/CameraController.h
)
