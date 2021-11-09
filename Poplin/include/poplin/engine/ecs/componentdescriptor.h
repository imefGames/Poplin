#pragma once

#include <poplin/core/reflection/typeinfo.h>
#include <poplin/engine/ecs/entity.h>
#include <functional>
#include <string>

namespace Poplin
{
    class Entity;

    class ComponentDescriptor
    {
    public:
        ComponentDescriptor(const std::string& name,
            const std::function<const TypeInfo*()>& getComponentTypeInfo,
            const std::function<bool(Entity& entity)>& hasFunction,
            const std::function<void*(Entity& entity)>& getComponentAddress,
            const std::function<void(Entity& entity)>& addFunction,
            const std::function<void(Entity& entity)>& removeFunction);

        inline const std::string& GetName() const { return m_Name; }

        const TypeInfo* GetComponentTypeInfo() const;
        bool EntityHasComponent(Entity& entity) const;
        void* GetComponentAddress(Entity& entity) const;
        void AddComponentToEntity(Entity& entity) const;
        void RemoveComponentFromEntity(Entity& entity) const;

    private:
        std::string m_Name;
        std::function<const TypeInfo* ()> m_GetComponentTypeInfo;
        std::function<bool(Entity& entity)> m_HasComponent;
        std::function<void* (Entity& entity)> m_GetComponentAddress;
        std::function<void(Entity& entity)> m_AddComponent;
        std::function<void(Entity& entity)> m_RemoveComponent;
    };

    namespace ComponentDescriptorUtils
    {
        template <class T>
        static bool HasComponent(Entity& entity)
        {
            return entity.HasComponent<T>();
        }

        template <class T>
        static void* GetComponentAddress(Entity& entity)
        {
            return &entity.GetComponent<T>();
        }

        template <class T>
        static void AddComponent(Entity& entity)
        {
            entity.AddComponent<T>();
        }

        template <class T>
        static void RemoveComponent(Entity& entity)
        {
            entity.RemoveComponent<T>();
        }

        template <class T>
        ComponentDescriptor* CreateComponentDescriptor(const std::string& name)
        {
            return new ComponentDescriptor{ name, &Reflection::GetTypeInfo<T>, &HasComponent<T>, &GetComponentAddress<T>, &AddComponent<T>, &RemoveComponent<T> };
        }
    }
}