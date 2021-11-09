#include <poplin/engine/asset/assetlocator.h>

#include <poplin/core/error.h>
#include <poplin/core/reflection/typeinfo.h>
#include <poplin/core/reflection/reflectedtyperegistry.h>
#include <poplin/core/serialization/serializer.h>
#include <json.hpp>
#include <istream>
#include <fstream>

namespace Poplin
{
    AssetLocator::AssetLocator()
    {
        RegisterInstance(this);

        std::string filePath{ "Assets/AssetRegistry.json" };
        std::ifstream inFile{ filePath };

        nlohmann::json data;
        if (inFile.is_open())
        {
            inFile >> data;
        }
        else
        {
            PoplinWarning(false, "Failed to open asset registry.");
        }

        const ReflectedTypeRegistry& typeRegistry{ ReflectedTypeRegistry::Get() };

        for (const nlohmann::json& assetData : data["AssetList"])
        {
            AssetID assetID{ assetData["AssetID"].get<AssetID>() };
            TypeID typeID{ assetData["TypeID"].get<TypeID>() };

            std::shared_ptr<ManagedAsset> newAsset{};
            if (const TypeInfo* typeInfo = typeRegistry.FindTypeInfo(typeID))
            {
                if (typeInfo->IsAManagedAsset())
                {
                    newAsset = std::shared_ptr<ManagedAsset>{ (ManagedAsset*)typeInfo->InstantiateType() };
                    if (newAsset)
                    {
                        newAsset->SetTypeInfo(typeInfo);
                        newAsset->SetAssetID(assetID);
                        newAsset->SetName(assetData["AssetName"].get<std::string>());
                        Serializer::LoadObject(newAsset.get(), *typeInfo, assetData);
                        newAsset->OnAssetLoaded();
                        m_LoadedAssets[assetID] = newAsset;
                    }
                    else
                    {
                        PoplinWarning(false, "Failed to instantiate asset.");
                    }
                }
                else
                {
                    PoplinWarning(false, "Asset is not a Managed Asset.");
                }
            }
            else
            {
                PoplinWarning(false, "Failed to load asset.");
            }
        }
    }

    AssetLocator::~AssetLocator()
    {
        UnregisterInstance(this);
    }

    std::shared_ptr<ManagedAsset> AssetLocator::FindAsset(AssetID assetID) const
    {
        std::shared_ptr<ManagedAsset> foundAsset{};
        auto foundIt{ m_LoadedAssets.find(assetID) };
        if (foundIt != m_LoadedAssets.end())
        {
            foundAsset = foundIt->second;
        }
        return foundAsset;
    }
}