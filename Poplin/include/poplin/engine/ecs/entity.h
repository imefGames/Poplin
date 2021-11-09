#pragma once

#include <poplin/core/types.hpp>
#include <poplin/core/reflection/typeinfo.h>
#include <poplin/engine/ecs/entityregistry.h>
#include <poplin/engine/ecs/components/entitymetadatacomponent.h>

namespace Poplin
{
    class Entity
    {
    public:
        Entity() = default;
        Entity(EntityRegistry& registry, entt::entity entity);

        inline u32 GetEntityID() const { return static_cast<u32>(m_Handle.entity()); }

        template <class T>
        bool HasComponent()
        {
            return m_Handle.has<T>();
        }

        template <class T>
        T& GetComponent()
        {
            return m_Handle.get<T>();
        }

        template <class T, class... Args>
        T& AddComponent(Args... args)
        {
            //TODO if def in editor
            EntityMetaDataComponent& metaData{ GetComponent<EntityMetaDataComponent>() };
            if (const TypeInfo* foundType = Reflection::GetTypeInfo<T>())
            {
                metaData.OwnedComponentTypes.push_back(foundType);
            }
            return m_Handle.emplace<T>(std::forward<Args>(args)...);
        }

        template <>
        EntityMetaDataComponent& AddComponent<EntityMetaDataComponent>()
        {
            return m_Handle.emplace<EntityMetaDataComponent>();
        }

        template <class T>
        void RemoveComponent()
        {
            EntityMetaDataComponent& metaData{ GetComponent<EntityMetaDataComponent>() };
            const TypeInfo* typeToRemove{ Reflection::GetTypeInfo<T>() };
            auto removeByID{ [typeToRemove](const TypeInfo* type) { return type->GetTypeID() == typeToRemove->GetTypeID(); } };
            auto endIt{ std::remove_if(metaData.OwnedComponentTypes.begin(), metaData.OwnedComponentTypes.end(), removeByID) };
            metaData.OwnedComponentTypes.erase(endIt, metaData.OwnedComponentTypes.end());
            m_Handle.remove<T>();
        }

    private:
        using EntityHandle = entt::basic_handle<entt::entity>;
        EntityHandle m_Handle;
    };
}