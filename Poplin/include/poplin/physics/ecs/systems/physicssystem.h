#pragma once

#include <poplin/core/types.hpp>
#include <poplin/engine/ecs/system.h>

namespace Poplin
{
    class RigidBodyComponent;
    class TransformComponent;

    class PhysicsSystem : public System
    {
    public:
        PhysicsSystem(SystemUpdater& updater);

    private:
        void PreWorldUpdate(f32 deltaTime, TransformComponent& transform, RigidBodyComponent& rigidBody);
        void UpdateWorld(f32 deltaTime);
        void PostWorldUpdate(f32 deltaTime, TransformComponent& transform, RigidBodyComponent& rigidBody);
    };
}