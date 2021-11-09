#pragma once

#include <box2d/box2d.h>
#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <poplin/core/types.hpp>
#include <poplin/core/reflection/enuminfo.h>
#include <poplin/core/reflection/typeinfo.h>
#include <poplin/engine/ecs/componentdescriptor.h>
#include <memory>

namespace Poplin
{
    class RigidBodyComponent;

    namespace RigidBodyComponentUtils
    {
        void InitRigidBody(RigidBodyComponent& rigidBody, Entity& entity);
        void ShutdownRigidBody(RigidBodyComponent& rigidBody, Entity& entity);
    }

    class RigidBodyComponent
    {
        friend class PhysicsWorld;
        friend class PhysicsSystem;
        friend void RigidBodyComponentUtils::InitRigidBody(RigidBodyComponent&, Entity&);
        friend void RigidBodyComponentUtils::ShutdownRigidBody(RigidBodyComponent&, Entity&);

    public:
        struct RigidBodyUserData
        {
            Entity m_Entity;
        };

        RigidBodyComponent();

        glm::vec2 GetLinearVelocity() const;
        void SetLinearVelocity(const glm::vec2& velocity);

        static u32& GetRigidBodyType(RigidBodyComponent& rigidBody);
        static void SetRigidBodyType(RigidBodyComponent& rigidBody, const u32& type);

        static bool& GetRigidBodyFixedRotation(RigidBodyComponent& rigidBody);
        static void SetRigidBodyFixedRotation(RigidBodyComponent& rigidBody, const bool& fixedRotation);

        static bool& GetRigidBodyIsATrigger(RigidBodyComponent& rigidBody);
        static void SetRigidBodyIsATrigger(RigidBodyComponent& rigidBody, const bool& isATrigger);

    private:

        std::unique_ptr<RigidBodyUserData> m_UserData;
        b2Body* m_B2Body;
    };



    static const EnumInfo::EnumEntry g_RigidBodyTypeEnumValues[]
    {
            { 0, "Static" },
            { 1, "Kinematic" },
            { 2, "Dynamic" }
    };
    static const EnumInfo g_RigidBodyTypeEnum{ 156941, g_RigidBodyTypeEnumValues, 3 };

    namespace Enums
    {
        template <>
        static const EnumInfo* GetEnumInfo<b2BodyType>()
        {
            return &g_RigidBodyTypeEnum;
        }
    }

    static const PropertyInfo g_RigidBodyComponentPropertiesInfo[]
    {
        { 0, "Type", u32Max, EPropertyType::U32, EPropertyVisibility::Public, 156941, PropertyInfo::Flags::IsEnum, new PropertyAccessorImpl<RigidBodyComponent, u32>(&RigidBodyComponent::GetRigidBodyType, &RigidBodyComponent::SetRigidBodyType) },
        { 1, "FixedRotation", u32Max, EPropertyType::Bool, EPropertyVisibility::Public, 0, PropertyInfo::Flags::None, new PropertyAccessorImpl<RigidBodyComponent, bool>(&RigidBodyComponent::GetRigidBodyFixedRotation, &RigidBodyComponent::SetRigidBodyFixedRotation) },
        { 2, "IsATrigger", u32Max, EPropertyType::Bool, EPropertyVisibility::Public, 0, PropertyInfo::Flags::None, new PropertyAccessorImpl<RigidBodyComponent, bool>(&RigidBodyComponent::GetRigidBodyIsATrigger, &RigidBodyComponent::SetRigidBodyIsATrigger) },
    };
    static const TypeInfo g_RigidBodyComponentTypeInfo
    (
        912,
        "Rigid Body",
        sizeof(RigidBodyComponent),
        g_RigidBodyComponentPropertiesInfo,
        sizeof(g_RigidBodyComponentPropertiesInfo) / sizeof(PropertyInfo),
        nullptr
    );

    namespace Reflection
    {
        template <>
        static const TypeInfo* GetTypeInfo<RigidBodyComponent>()
        {
            return &g_RigidBodyComponentTypeInfo;
        }
    }

    namespace ComponentDescriptorUtils
    {
        //TODO: move elsewhere ?
        template <>
        static void AddComponent<RigidBodyComponent>(Entity& entity)
        {
            RigidBodyComponent& rigidBody{ entity.AddComponent<RigidBodyComponent>() };
            RigidBodyComponentUtils::InitRigidBody(rigidBody, entity);
        }

        template <>
        static void RemoveComponent<RigidBodyComponent>(Entity& entity)
        {
            RigidBodyComponent& rigidBody{ entity.GetComponent<RigidBodyComponent>() };
            RigidBodyComponentUtils::ShutdownRigidBody(rigidBody, entity);
            entity.RemoveComponent<RigidBodyComponent>();
        }
    }
}