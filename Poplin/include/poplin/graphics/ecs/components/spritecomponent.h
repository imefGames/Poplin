#pragma once

#include <poplin/core/reflection/typeinfo.h>
#include <poplin/engine/ecs/componentdescriptor.h>
#include <glm/glm.hpp>
#include <imgui/imgui.h>

namespace Poplin
{
    class TextureAsset;

    class SpriteComponent
    {
    public:
        SpriteComponent();

        std::shared_ptr<TextureAsset> SpriteTexture;
        glm::vec2 UVRepeat;
        glm::vec2 UVOffset;
    };



    static const PropertyInfo g_SpriteComponentPropertiesInfo[]
    {
        { 0, "SpriteTexture", 0, EPropertyType::TypeInstancePointer, EPropertyVisibility::Public, 11111, PropertyInfo::Flags::IsManagedAsset },
        { 1, "UVRepeat", sizeof(std::shared_ptr<TextureAsset>) + 0, EPropertyType::Vector2, EPropertyVisibility::Public },
        { 2, "UVOffset", sizeof(std::shared_ptr<TextureAsset>) + 8, EPropertyType::Vector2, EPropertyVisibility::Public }
    };
    static const TypeInfo g_SpriteComponentTypeInfo
    (
        1468,
        "Sprite",
        sizeof(SpriteComponent),
        g_SpriteComponentPropertiesInfo,
        sizeof(g_SpriteComponentPropertiesInfo) / sizeof(PropertyInfo),
        nullptr
    );

    namespace Reflection
    {
        template <>
        static const TypeInfo* GetTypeInfo<SpriteComponent>()
        {
            return &g_SpriteComponentTypeInfo;
        }
    }
}