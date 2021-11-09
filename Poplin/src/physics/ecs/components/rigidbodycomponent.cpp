#include <poplin/physics/ecs/components/rigidbodycomponent.h>

#include <poplin/engine/ecs/world.h>
#include <poplin/engine/ecs/universe.h>

namespace Poplin
{
    RigidBodyComponent::RigidBodyComponent()
        : m_B2Body{ nullptr }
    {
    }

    glm::vec2 RigidBodyComponent::GetLinearVelocity() const
    {
        const b2Vec2& velocity{ m_B2Body->GetLinearVelocity() };
        return glm::vec2{ velocity.x, velocity.y };
    }

    void RigidBodyComponent::SetLinearVelocity(const glm::vec2& velocity)
    {
        m_B2Body->SetLinearVelocity(b2Vec2{ velocity.x, velocity.y });
    }

    u32& RigidBodyComponent::GetRigidBodyType(RigidBodyComponent& rigidBody)
    {
        static u32 bodyType{};
        bodyType = (u32)rigidBody.m_B2Body->GetType();
        return bodyType;
    }

    void RigidBodyComponent::SetRigidBodyType(RigidBodyComponent& rigidBody, const u32& type)
    {
        rigidBody.m_B2Body->SetType((const b2BodyType&)type);
    }

    bool& RigidBodyComponent::GetRigidBodyFixedRotation(RigidBodyComponent& rigidBody)
    {
        static bool rotationFixed{};
        rotationFixed = rigidBody.m_B2Body->IsFixedRotation();
        return rotationFixed;
    }

    void RigidBodyComponent::SetRigidBodyFixedRotation(RigidBodyComponent& rigidBody, const bool& fixedRotation)
    {
        rigidBody.m_B2Body->SetFixedRotation(fixedRotation);
    }

    bool& RigidBodyComponent::GetRigidBodyIsATrigger(RigidBodyComponent& rigidBody)
    {
        static bool isATrigger{};
        isATrigger = rigidBody.m_B2Body->GetFixtureList()->IsSensor();
        return isATrigger;
    }

    void RigidBodyComponent::SetRigidBodyIsATrigger(RigidBodyComponent& rigidBody, const bool& isATrigger)
    {
        rigidBody.m_B2Body->GetFixtureList()->SetSensor(isATrigger);
    }

    namespace RigidBodyComponentUtils
    {
        void InitRigidBody(RigidBodyComponent& rigidBody, Entity& entity)
        {
            if (World* currentWorld = Universe::Get().GetCurrentWorld()) //TODO: get world from entity
            {
                currentWorld->GetPhysicsWorld().InitRigidBody(rigidBody);

                rigidBody.m_UserData = std::make_unique<RigidBodyComponent::RigidBodyUserData>();
                rigidBody.m_UserData->m_Entity = entity;
                rigidBody.m_B2Body->GetUserData().pointer = (uintptr_t)rigidBody.m_UserData.get();
            }
        }

        void ShutdownRigidBody(RigidBodyComponent& rigidBody, Entity& entity)
        {
            if (World* currentWorld = Universe::Get().GetCurrentWorld())
            {
                currentWorld->GetPhysicsWorld().ShutdownRigidBody(rigidBody);
                
                rigidBody.m_UserData.reset();
            }
        }
    }
}