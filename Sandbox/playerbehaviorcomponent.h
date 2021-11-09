#pragma once

#include <poplin/core/types.hpp>
#include <poplin/engine/ecs/components/logiccomponent.h>
#include <poplin/engine/input/input.h>
#include <poplin/physics/ecs/components/rigidbodycomponent.h>

namespace Poplin
{
    class PlayerBehaviorComponent : public LogicComponentBehavior
    {
    public:
        void Update(f32 deltaTime) override
        {
            if (m_Entity.HasComponent<RigidBodyComponent>())
            {
                RigidBodyComponent& rigidBody{ m_Entity.GetComponent<RigidBodyComponent>() };

                glm::vec2 velocity{ rigidBody.GetLinearVelocity() };
                if (Input::IsKeyDown(Input::EKeyCode::ArrowLeft))
                {
                    velocity.x = -Speed;
                }
                if (Input::IsKeyDown(Input::EKeyCode::ArrowRight))
                {
                    velocity.x = Speed;
                }
                if (std::fabs(velocity.y) <= 0.01f && Input::IsKeyDown(Input::EKeyCode::ArrowUp))
                {
                    velocity.y -= 5.0f;
                }

                rigidBody.SetLinearVelocity(velocity);
            }
        }

        f32 Speed{ 1.0f };
    };
    
    
    
    static const PropertyInfo g_PlayerBehaviorComponentPropertiesInfo[]
    {
        { 0, "Speed", offsetof(PlayerBehaviorComponent, Speed), EPropertyType::F32, EPropertyVisibility::Public },
    };
    static const TypeInfo g_PlayerBehaviorComponentTypeInfo
    (
        1369882,
        "PlayerBehavior",
        sizeof(PlayerBehaviorComponent),
        g_PlayerBehaviorComponentPropertiesInfo,
        sizeof(g_PlayerBehaviorComponentPropertiesInfo) / sizeof(PropertyInfo),
        nullptr
    );

    namespace Reflection
    {
        template <>
        static const TypeInfo* GetTypeInfo<PlayerBehaviorComponent>()
        {
            return &g_PlayerBehaviorComponentTypeInfo;
        }
    }
}