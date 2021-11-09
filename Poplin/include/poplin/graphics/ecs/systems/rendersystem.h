#pragma once

#include <poplin/core/types.hpp>
#include <poplin/engine/ecs/system.h>

namespace Poplin
{
    class CameraComponent;
    class SpriteComponent;
    class TransformComponent;

    class RenderSystem : public System
    {
    public:
        RenderSystem(SystemUpdater& updater);

    private:
        void UpdateCamera(f32 deltaTime, TransformComponent& transform, CameraComponent& camera);
        void RenderSprite(f32 deltaTime, TransformComponent& transform, SpriteComponent& sprite);
    };
}