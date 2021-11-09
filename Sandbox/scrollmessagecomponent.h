#pragma once

#include <poplin/core/types.hpp>
#include <poplin/engine/ecs/components/logiccomponent.h>
#include <poplin/engine/input/input.h>
#include <poplin/graphics/ecs/components/spritecomponent.h>

namespace Poplin
{
    class ScrollMessageComponent : public LogicComponentBehavior
    {
    public:
        void Update(f32 deltaTime) override
        {
            if (m_Entity.HasComponent<SpriteComponent>())
            {
                SpriteComponent& sprite{ m_Entity.GetComponent<SpriteComponent>() };
                sprite.UVOffset.x += Speed * deltaTime;
            }
        }

        f32 Speed{ 0.1f };
    };
    
    
    
    static const PropertyInfo g_ScrollMessageComponentPropertiesInfo[]
    {
        { 0, "Speed", offsetof(ScrollMessageComponent, Speed), EPropertyType::F32, EPropertyVisibility::Public },
    };
    static const TypeInfo g_ScrollMessageComponentTypeInfo
    (
        15623,
        "ScrollMessage",
        sizeof(ScrollMessageComponent),
        g_ScrollMessageComponentPropertiesInfo,
        sizeof(g_ScrollMessageComponentPropertiesInfo) / sizeof(PropertyInfo),
        nullptr
    );

    namespace Reflection
    {
        template <>
        static const TypeInfo* GetTypeInfo<ScrollMessageComponent>()
        {
            return &g_ScrollMessageComponentTypeInfo;
        }
    }
}