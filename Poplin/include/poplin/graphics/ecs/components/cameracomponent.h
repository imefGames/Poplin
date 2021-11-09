#pragma once

#include <poplin/core/types.hpp>
#include <poplin/core/reflection/typeinfo.h>
#include <poplin/engine/ecs/componentdescriptor.h>
#include <glm/glm.hpp>
#include <imgui/imgui.h>

namespace Poplin
{
    class Texture;

    class CameraComponent
    {
    public:
        CameraComponent();

        glm::mat4 ComputeProjection() const;

        glm::vec2 TopLeft;
        glm::vec2 BottomRight;
        f32 Near;
        f32 Far;
    };



    static const PropertyInfo g_CameraComponentPropertiesInfo[]
    {
        { 0, "TopLeft", 0, EPropertyType::Vector2, EPropertyVisibility::Public },
        { 1, "BottomRight", 8, EPropertyType::Vector2, EPropertyVisibility::Public },
        { 2, "Near", 16, EPropertyType::F32, EPropertyVisibility::Public },
        { 3, "Far", 20, EPropertyType::F32, EPropertyVisibility::Public }
    };
    static const TypeInfo g_CameraComponentTypeInfo
    (
        96315,
        "Camera",
        sizeof(CameraComponent),
        g_CameraComponentPropertiesInfo,
        sizeof(g_CameraComponentPropertiesInfo) / sizeof(PropertyInfo),
        nullptr
    );

    namespace Reflection
    {
        template <>
        static const TypeInfo* GetTypeInfo<CameraComponent>()
        {
            return &g_CameraComponentTypeInfo;
        }
    }
}