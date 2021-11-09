#pragma once

#include <poplin/core/singleton.hpp>
#include <poplin/core/types.hpp>
#include <poplin/core/reflection/typeinfo.h>
#include <string>

namespace Poplin
{
    using AssetID = u64;
    static const AssetID InvalidAssetID = u64Max;

    class ManagedAsset
    {
        friend class AssetLocator;

    public:
        ManagedAsset();
        ~ManagedAsset() = default;

        inline const std::string& GetName() const { return m_Name; }
        inline const TypeInfo* GetTypeInfo() const { return m_TypeInfo; }
        inline AssetID GetAssetID() const { return m_AssetID; }

    protected:
        virtual void OnAssetLoaded() {};

    private:
        inline void SetName(const std::string& name) { m_Name = name; }
        inline void SetTypeInfo(const TypeInfo* typeInfo) { m_TypeInfo = typeInfo; }
        inline void SetAssetID(AssetID assetID) { m_AssetID = assetID; }

        std::string m_Name;
        const TypeInfo* m_TypeInfo;
        AssetID m_AssetID;
    };
}