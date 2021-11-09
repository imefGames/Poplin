#pragma once

#include <poplin/core/reflection/typeinfo.h>
#include <poplin/engine/asset/managedasset.h>
#include <poplin/graphics/texture.h>
#include <string>

namespace Poplin
{
    class TextureAsset : public ManagedAsset
    {
    private:
        void OnAssetLoaded() override;

    public:
        std::string FilePath;
        std::shared_ptr<Texture> Texture;
    };



    static const PropertyInfo g_TextureAssetPropertiesInfo[]
    {
        { 0, "FilePath", offsetof(TextureAsset, FilePath), EPropertyType::String, EPropertyVisibility::Public }
    };
    static const TypeInfo g_TextureAssetTypeInfo
    (
        11111,
        "Texture Asset",
        sizeof(TextureAsset),
        g_TextureAssetPropertiesInfo,
        sizeof(g_TextureAssetPropertiesInfo) / sizeof(PropertyInfo),
        Reflection::InstantiateType<TextureAsset>,
        TypeInfo::Flags::IsManagedAsset
    );

    namespace Reflection
    {
        template <>
        static const TypeInfo* GetTypeInfo<TextureAsset>()
        {
            return &g_TextureAssetTypeInfo;
        }
    }
}