#include <poplin/core/serialization/serializer.h>

#include <poplin/core/types.hpp>
#include <poplin/engine/asset/assetlocator.h>

namespace Poplin
{
    namespace Serializer
    {
        namespace Internal
        {
            static void LoadDataProperty(void* dataAddress, const PropertyInfo& propertyInfo, const nlohmann::json& data)
            {
                switch (propertyInfo.GetType())
                {
                    case EPropertyType::Bool:
                    {
                        auto b = data[propertyInfo.GetName()].get<bool>();
                        propertyInfo.SetPropertyAddressAs(dataAddress, b);
                        break;
                    }
                    case EPropertyType::U8:
                    {
                        auto i = data[propertyInfo.GetName()].get<u8>();
                        propertyInfo.SetPropertyAddressAs(dataAddress, i);
                        break;
                    }
                    case EPropertyType::U16:
                    {
                        auto i = data[propertyInfo.GetName()].get<u16>();
                        propertyInfo.SetPropertyAddressAs(dataAddress, i);
                        break;
                    }
                    case EPropertyType::U32:
                    {
                        auto i = data[propertyInfo.GetName()].get<u32>();
                        propertyInfo.SetPropertyAddressAs(dataAddress, i);
                        break;
                    }
                    case EPropertyType::U64:
                    {
                        auto i = data[propertyInfo.GetName()].get<u64>();
                        propertyInfo.SetPropertyAddressAs(dataAddress, i);
                        break;
                    }
                    case EPropertyType::S8:
                    {
                        auto i = data[propertyInfo.GetName()].get<s8>();
                        propertyInfo.SetPropertyAddressAs(dataAddress, i);
                        break;
                    }
                    case EPropertyType::S16:
                    {
                        auto i = data[propertyInfo.GetName()].get<s16>();
                        propertyInfo.SetPropertyAddressAs(dataAddress, i);
                        break;
                    }
                    case EPropertyType::S32:
                    {
                        auto i = data[propertyInfo.GetName()].get<s32>();
                        propertyInfo.SetPropertyAddressAs(dataAddress, i);
                        break;
                    }
                    case EPropertyType::S64:
                    {
                        auto i = data[propertyInfo.GetName()].get<s64>();
                        propertyInfo.SetPropertyAddressAs(dataAddress, i);
                        break;
                    }
                    case EPropertyType::F32:
                    {
                        auto i = data[propertyInfo.GetName()].get<f32>();
                        propertyInfo.SetPropertyAddressAs(dataAddress, i);
                        break;
                    }
                    case EPropertyType::Vector2:
                    {
                        glm::vec2 v
                        {
                            data[propertyInfo.GetName()]["x"].get<f32>(),
                            data[propertyInfo.GetName()]["y"].get<f32>()
                        };
                        propertyInfo.SetPropertyAddressAs(dataAddress, v);
                        break;
                    }
                    case EPropertyType::Vector3:
                    {
                        glm::vec3 v
                        {
                            data[propertyInfo.GetName()]["x"].get<f32>(),
                            data[propertyInfo.GetName()]["y"].get<f32>(),
                            data[propertyInfo.GetName()]["z"].get<f32>()
                        };
                        propertyInfo.SetPropertyAddressAs(dataAddress, v);
                        break;
                    }
                    case EPropertyType::Vector4:
                    {
                        glm::vec4 v
                        {
                            data[propertyInfo.GetName()]["x"].get<f32>(),
                            data[propertyInfo.GetName()]["y"].get<f32>(),
                            data[propertyInfo.GetName()]["z"].get<f32>(),
                            data[propertyInfo.GetName()]["w"].get<f32>()
                        };
                        propertyInfo.SetPropertyAddressAs(dataAddress, v);
                        break;
                    }
                    case EPropertyType::String:
                    {
                        propertyInfo.SetPropertyAddressAs(dataAddress, data[propertyInfo.GetName()].get<std::string>());
                        break;
                    }
                    case EPropertyType::TypeInstance:
                    {
                        PoplinAssert(false, "Unhandled PropertyType.");
                        break;
                    }
                    case EPropertyType::TypeInstancePointer:
                    {
                        if (propertyInfo.IsAManagedAsset())
                        {
                            std::shared_ptr<ManagedAsset> foundAsset{ AssetLocator::Get().FindAsset(data[propertyInfo.GetName()].get<AssetID>()) };
                            std::shared_ptr<ManagedAsset>* propertyPtr{ propertyInfo.GetPropertyAddressAs<std::shared_ptr<ManagedAsset>>(dataAddress) };

                            *propertyPtr = foundAsset;
                        }
                        else
                        {
                            PoplinAssert(false, "Unhandled PropertyType.");
                        }
                        break;
                    }
                    default:
                    {
                        PoplinAssert(false, "Unknown PropertyType.");
                        break;
                    }
                }
            }
        }

        void LoadObject(void* objectPtr, const TypeInfo& type, const nlohmann::json& data)
        {
            auto loadFunction
            {
                [objectPtr, &data](const PropertyInfo& propertyInfo)
                {
                    Internal::LoadDataProperty(objectPtr, propertyInfo, data);
                }
            };
            type.ForEachProperty(loadFunction);
        }
    }
}