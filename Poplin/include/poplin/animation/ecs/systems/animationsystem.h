#pragma once

#include <poplin/core/types.hpp>
#include <poplin/engine/ecs/system.h>

namespace Poplin
{
    class AnimatorComponent;
    class SpriteComponent;

    class AnimationSystem : public System
    {
    public:
        AnimationSystem(SystemUpdater& updater);

    private:
        void UpdateAnimation(f32 deltaTime, AnimatorComponent& animator, SpriteComponent& sprite);
    };
}