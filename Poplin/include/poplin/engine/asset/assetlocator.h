#pragma once

#include <poplin/core/singleton.hpp>
#include <poplin/engine/asset/managedasset.h>
#include <map>
#include <memory>

namespace Poplin
{
    class AssetLocator : public Singleton<AssetLocator>
    {
    public:
        AssetLocator();
        ~AssetLocator();

        std::shared_ptr<ManagedAsset> FindAsset(AssetID assetID) const;

        inline const std::map<AssetID, std::shared_ptr<ManagedAsset>>& GetAllLoadedAssets() const { return m_LoadedAssets; }

    private:
        std::map<AssetID, std::shared_ptr<ManagedAsset>> m_LoadedAssets;
    };
}