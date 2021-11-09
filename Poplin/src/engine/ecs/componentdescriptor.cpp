#include <poplin/engine/ecs/componentdescriptor.h>

namespace Poplin
{
    ComponentDescriptor::ComponentDescriptor(const std::string& name,
        const std::function<const TypeInfo* ()>& getComponentTypeInfo,
        const std::function<bool(Entity& entity)>& hasFunction,
        const std::function<void* (Entity& entity)>& getComponentAddress,
        const std::function<void(Entity& entity)>& addFunction,
        const std::function<void(Entity& entity)>& removeFunction)
        : m_Name{ name }
        , m_GetComponentTypeInfo{ getComponentTypeInfo }
        , m_HasComponent{ hasFunction }
        , m_GetComponentAddress{ getComponentAddress }
        , m_AddComponent{ addFunction }
        , m_RemoveComponent{ removeFunction }
    {
    }

    const TypeInfo* ComponentDescriptor::GetComponentTypeInfo() const
    {
        return m_GetComponentTypeInfo();
    }

    bool ComponentDescriptor::EntityHasComponent(Entity& entity) const
    {
        return m_HasComponent(entity);
    }

    void* ComponentDescriptor::GetComponentAddress(Entity& entity) const
    {
        return m_GetComponentAddress(entity);
    }

    void ComponentDescriptor::AddComponentToEntity(Entity& entity) const
    {
        m_AddComponent(entity);
    }

    void ComponentDescriptor::RemoveComponentFromEntity(Entity& entity) const
    {
        m_RemoveComponent(entity);
    }
}