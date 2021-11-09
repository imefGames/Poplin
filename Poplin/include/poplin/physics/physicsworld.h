#pragma once

#include <box2d/box2d.h>
#include <poplin/core/types.hpp>
#include <poplin/physics/physicscontactlistener.h>

namespace Poplin
{
    class RigidBodyComponent;

    class PhysicsWorld
    {
        friend class PhysicsSystem;
    public:
        PhysicsWorld();

        void InitRigidBody(RigidBodyComponent& rigidBody);
        void ShutdownRigidBody(RigidBodyComponent& rigidBody);

        void ClearWorld();

    private:
        void Update(f32 deltaTime);

        b2World m_B2World;
        PhysicsContactListener m_ContactListener;
    };
}