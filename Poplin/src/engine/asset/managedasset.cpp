#include <poplin/engine/asset/managedasset.h>

namespace Poplin
{
    ManagedAsset::ManagedAsset()
        : m_TypeInfo{ nullptr }
        , m_AssetID{ InvalidAssetID }
    {
    }
}