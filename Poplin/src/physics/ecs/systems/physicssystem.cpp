#include <poplin/physics/ecs/systems/physicssystem.h>

#include <poplin/core/error.h>
#include <poplin/engine/ecs/systemupdater.h>
#include <poplin/engine/ecs/world.h>
#include <poplin/engine/ecs/universe.h>
#include <poplin/engine/ecs/components/transformcomponent.h>
#include <poplin/physics/ecs/components/rigidbodycomponent.h>

namespace Poplin
{
    PhysicsSystem::PhysicsSystem(SystemUpdater& updater)
        : System{ updater }
    {
        updater.RegisterSystemUpdate(this, &PhysicsSystem::PreWorldUpdate);
        updater.RegisterSystemUpdate(this, &PhysicsSystem::UpdateWorld);
        updater.RegisterSystemUpdate(this, &PhysicsSystem::PostWorldUpdate);
    }

    void PhysicsSystem::PreWorldUpdate(f32 deltaTime, TransformComponent& transform, RigidBodyComponent& rigidBody)
    {
        //TODO: get colliders

        b2Vec2 position{ transform.Position.x, transform.Position.y };
        rigidBody.m_B2Body->SetTransform(position, glm::radians(transform.Rotation.y));

        if (b2Fixture* fixture = rigidBody.m_B2Body->GetFixtureList())
        {
            switch (fixture->GetType())
            {
                case b2Shape::e_polygon:
                {
                    b2PolygonShape* polygon{ static_cast<b2PolygonShape*>(fixture->GetShape()) };
                    polygon->SetAsBox(transform.Scale.x * 0.5f, transform.Scale.y * 0.5f);
                    break;
                }
                default:
                {
                    PoplinAssert(false, "Unhandled shape type.")
                    break;
                }
            }
        }
    }

    void PhysicsSystem::UpdateWorld(f32 deltaTime)
    {
        if (World* currentWorld = Universe::Get().GetCurrentWorld())
        {
            currentWorld->GetPhysicsWorld().Update(deltaTime);
        }
    }

    void PhysicsSystem::PostWorldUpdate(f32 deltaTime, TransformComponent& transform, RigidBodyComponent& rigidBody)
    {
        b2Vec2 position{ rigidBody.m_B2Body->GetPosition() };
        //TODO: handle angle
        transform.Rotation.y = glm::degrees(rigidBody.m_B2Body->GetAngle());
        transform.Position = glm::vec3{ position.x, position.y, transform.Position.z };
    }
}