#pragma once

#include <poplin/core/reflection/typeinfo.h>
#include <poplin/engine/ecs/componentdescriptor.h>
#include <glm/glm.hpp>
#include <imgui/imgui.h>

namespace Poplin
{
    class TransformComponent
    {
    public:
        TransformComponent();

        glm::mat4 ComputeGlobalTransform() const;

        glm::vec3 Position;
        glm::vec3 Rotation;
        glm::vec3 Scale;
        glm::vec3 Origin;
        //TODO: local transform
    };



    static const PropertyInfo g_TransformComponentPropertiesInfo[]
    {
        { 0, "Position", 0, EPropertyType::Vector3, EPropertyVisibility::Public },
        { 1, "Rotation", 12, EPropertyType::Vector3, EPropertyVisibility::Public },
        { 2, "Scale", 24, EPropertyType::Vector3, EPropertyVisibility::Public },
        { 3, "Origin", 36, EPropertyType::Vector3, EPropertyVisibility::Public }
    };
    static const TypeInfo g_TransformComponentTypeInfo
    (
        1234,
        "Transform",
        sizeof(TransformComponent),
        g_TransformComponentPropertiesInfo,
        sizeof(g_TransformComponentPropertiesInfo) / sizeof(PropertyInfo),
        nullptr
    );

    namespace Reflection
    {
        template <>
        static const TypeInfo* GetTypeInfo<TransformComponent>()
        {
            return &g_TransformComponentTypeInfo;
        }
    }
}