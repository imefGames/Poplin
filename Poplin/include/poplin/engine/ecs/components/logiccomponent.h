#pragma once

#include <poplin/core/types.hpp>
#include <poplin/core/reflection/typeinfo.h>
#include <poplin/engine/ecs/componentdescriptor.h>
#include <poplin/engine/ecs/entity.h>
#include <memory>

namespace Poplin
{
    class LogicComponentBehavior
    {
        friend class LogicComponent;

    public:
        virtual ~LogicComponentBehavior() = default;

        virtual void Update(f32 deltaTime) = 0;

    protected:
        Entity m_Entity;
        const TypeInfo* m_TypeInfo;
    };

    class LogicComponent
    {
    public:
        LogicComponent();
        LogicComponent(const Entity& entity);

        bool HasBehaviorOfType(const TypeInfo* typeInfo) const;
        LogicComponentBehavior* GetBehaviorOfType(const TypeInfo* typeInfo);

        template <class T>
        void AddBehavior()
        {
            m_Behavior = std::make_unique<T>();
            m_Behavior->m_Entity = m_Entity;
            m_Behavior->m_TypeInfo = Reflection::GetTypeInfo<T>();
        }

        template <class T>
        void RemoveBehavior()
        {
            m_Behavior.reset();
        }

        void Update(f32 deltaTime);

    private:
        Entity m_Entity;
        std::unique_ptr<LogicComponentBehavior> m_Behavior;
    };


    namespace ComponentDescriptorUtils
    {
        template <class T>
        static bool HasLogicBehavior(Entity& entity)
        {
            bool hasLogicBehavior{ false };
            if (entity.HasComponent<LogicComponent>())
            {
                LogicComponent& logicComponent{ entity.GetComponent<LogicComponent>() };
                hasLogicBehavior = logicComponent.HasBehaviorOfType(Reflection::GetTypeInfo<T>());
            }
            return hasLogicBehavior;
        }

        template <class T>
        static void* GetLogicBehaviorAddress(Entity& entity)
        {
            void* address{ nullptr };
            if (entity.HasComponent<LogicComponent>())
            {
                LogicComponent& logicComponent{ entity.GetComponent<LogicComponent>() };
                address = logicComponent.GetBehaviorOfType(Reflection::GetTypeInfo<T>());
            }
            return address;
        }

        template <class T>
        static void AddLogicBehavior(Entity& entity)
        {
            if (!entity.HasComponent<LogicComponent>())
            {
                entity.AddComponent<LogicComponent>(entity);
            }

            //TODO if def in editor
            EntityMetaDataComponent& metaData{ entity.GetComponent<EntityMetaDataComponent>() };
            if (const TypeInfo* foundType = Reflection::GetTypeInfo<T>())
            {
                metaData.OwnedComponentTypes.push_back(foundType);
            }

            LogicComponent& logicComponent{ entity.GetComponent<LogicComponent>() };
            logicComponent.AddBehavior<T>();
        }

        template <class T>
        static void RemoveLogicBehavior(Entity& entity)
        {
            if (entity.HasComponent<LogicComponent>())
            {
                EntityMetaDataComponent& metaData{ entity.GetComponent<EntityMetaDataComponent>() };
                const TypeInfo* typeToRemove{ Reflection::GetTypeInfo<T>() };
                auto removeByID{ [typeToRemove](const TypeInfo* type) { return type->GetTypeID() == typeToRemove->GetTypeID(); } };
                auto endIt{ std::remove_if(metaData.OwnedComponentTypes.begin(), metaData.OwnedComponentTypes.end(), removeByID) };
                metaData.OwnedComponentTypes.erase(endIt, metaData.OwnedComponentTypes.end());

                LogicComponent& logicComponent{ entity.GetComponent<LogicComponent>() };
                logicComponent.RemoveBehavior<T>();
            };
        }

        template <class T>
        ComponentDescriptor* CreateLogicBehaviorDescriptor(const std::string& name)
        {
            return new ComponentDescriptor{ name, &Reflection::GetTypeInfo<T>, &HasLogicBehavior<T>, &GetLogicBehaviorAddress<T>, &AddLogicBehavior<T>, &RemoveLogicBehavior<T> };
        }
    }
}