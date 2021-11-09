#include <poplin/engine/ecs/components/logiccomponent.h>

namespace Poplin
{
    LogicComponent::LogicComponent()
        : m_Entity{}
    {
    }

    LogicComponent::LogicComponent(const Entity& entity)
        : m_Entity{ entity }
    {
    }

    bool LogicComponent::HasBehaviorOfType(const TypeInfo* typeInfo) const
    {
        return m_Behavior && m_Behavior->m_TypeInfo == typeInfo;
    }

    LogicComponentBehavior* LogicComponent::GetBehaviorOfType(const TypeInfo* typeInfo)
    {
        return HasBehaviorOfType(typeInfo) ? m_Behavior.get() : nullptr;
    }

    void LogicComponent::Update(f32 deltaTime)
    {
        if (m_Behavior)
        {
            m_Behavior->Update(deltaTime);
        }
    }
}