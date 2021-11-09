#include <poplin/physics/physicsworld.h>

#include <poplin/physics/ecs/components/rigidbodycomponent.h>

namespace Poplin
{
    PhysicsWorld::PhysicsWorld()
        : m_B2World{ b2Vec2{ 0.0f, 10.0f } }
    {
        m_B2World.SetContactListener(&m_ContactListener);
    }

    void PhysicsWorld::InitRigidBody(RigidBodyComponent& rigidBody)
    {
        b2BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        bodyDef.position.Set(0.0f, 0.0f);
        rigidBody.m_B2Body = m_B2World.CreateBody(&bodyDef);

        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(0.5f, 0.5f);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;
        rigidBody.m_B2Body->CreateFixture(&fixtureDef);
    }

    void PhysicsWorld::ShutdownRigidBody(RigidBodyComponent& rigidBody)
    {
        m_B2World.DestroyBody(rigidBody.m_B2Body);
    }

    void PhysicsWorld::ClearWorld()
    {
        b2Body* currentBody{ m_B2World.GetBodyList() };
        while (currentBody != nullptr)
        {
            b2Body* nextBody{ currentBody->GetNext() };
            m_B2World.DestroyBody(currentBody);
            currentBody = nextBody;
        }
    }

    void PhysicsWorld::Update(f32 deltaTime)
    {
        int32 velocityIterations = 6;
        int32 positionIterations = 2;

        m_B2World.Step(deltaTime, velocityIterations, positionIterations);
    }
}