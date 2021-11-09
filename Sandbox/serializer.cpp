#include "serializer.h"

#include <poplin/core/types.hpp>
#include <poplin/core/reflection/reflectedtyperegistry.h>
#include <poplin/engine/asset/assetlocator.h>
#include <poplin/engine/ecs/componentdescriptor.h>
#include <poplin/engine/ecs/componentdescriptorregistry.h>
#include <poplin/engine/ecs/entity.h>
#include <poplin/engine/ecs/universe.h>
#include <poplin/engine/ecs/world.h>

#include <json.hpp>
#include <iomanip>
#include <iostream>
#include <fstream>

namespace Poplin
{
    namespace Serializer
    {
        namespace Internal
        {
            static void SaveDataProperty(void* dataAddress, const PropertyInfo& propertyInfo, nlohmann::json& data)
            {
                switch (propertyInfo.GetType())
                {
                case EPropertyType::Bool:
                {
                    bool* b{ propertyInfo.GetPropertyAddressAs<bool>(dataAddress) };
                    data[propertyInfo.GetName()] = *b;
                    break;
                }
                case EPropertyType::U8:
                {
                    u8* i{ propertyInfo.GetPropertyAddressAs<u8>(dataAddress) };
                    data[propertyInfo.GetName()] = *i;
                    break;
                }
                case EPropertyType::U16:
                {
                    u16* i{ propertyInfo.GetPropertyAddressAs<u16>(dataAddress) };
                    data[propertyInfo.GetName()] = *i;
                    break;
                }
                case EPropertyType::U32:
                {
                    u32* i{ propertyInfo.GetPropertyAddressAs<u32>(dataAddress) };
                    data[propertyInfo.GetName()] = *i;
                    break;
                }
                case EPropertyType::U64:
                {
                    u64* i{ propertyInfo.GetPropertyAddressAs<u64>(dataAddress) };
                    data[propertyInfo.GetName()] = *i;
                    break;
                }
                case EPropertyType::S8:
                {
                    s8* i{ propertyInfo.GetPropertyAddressAs<s8>(dataAddress) };
                    data[propertyInfo.GetName()] = *i;
                    break;
                }
                case EPropertyType::S16:
                {
                    s16* i{ propertyInfo.GetPropertyAddressAs<s16>(dataAddress) };
                    data[propertyInfo.GetName()] = *i;
                    break;
                }
                case EPropertyType::S32:
                {
                    s32* i{ propertyInfo.GetPropertyAddressAs<s32>(dataAddress) };
                    data[propertyInfo.GetName()] = *i;
                    break;
                }
                case EPropertyType::S64:
                {
                    s64* i{ propertyInfo.GetPropertyAddressAs<s64>(dataAddress) };
                    data[propertyInfo.GetName()] = *i;
                    break;
                }
                case EPropertyType::F32:
                {
                    f32* f{ propertyInfo.GetPropertyAddressAs<f32>(dataAddress) };
                    data[propertyInfo.GetName()] = *f;
                    break;
                }
                case EPropertyType::Vector2:
                {
                    glm::vec2* v{ propertyInfo.GetPropertyAddressAs<glm::vec2>(dataAddress) };
                    data[propertyInfo.GetName()]["x"] = v->x;
                    data[propertyInfo.GetName()]["y"] = v->y;
                    break;
                }
                case EPropertyType::Vector3:
                {
                    glm::vec3* v{ propertyInfo.GetPropertyAddressAs<glm::vec3>(dataAddress) };
                    data[propertyInfo.GetName()]["x"] = v->x;
                    data[propertyInfo.GetName()]["y"] = v->y;
                    data[propertyInfo.GetName()]["z"] = v->z;
                    break;
                }
                case EPropertyType::Vector4:
                {
                    glm::vec4* v{ propertyInfo.GetPropertyAddressAs<glm::vec4>(dataAddress) };
                    data[propertyInfo.GetName()]["x"] = v->x;
                    data[propertyInfo.GetName()]["y"] = v->y;
                    data[propertyInfo.GetName()]["z"] = v->z;
                    data[propertyInfo.GetName()]["w"] = v->w;
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
                        std::shared_ptr<ManagedAsset>* propertyPtr{ propertyInfo.GetPropertyAddressAs<std::shared_ptr<ManagedAsset>>(dataAddress) };
                        AssetID assetID{ *propertyPtr ? (*propertyPtr)->GetAssetID() : InvalidAssetID };
                        data[propertyInfo.GetName()] = assetID;
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

            static void SaveEntity(Entity& entity, nlohmann::json& data)
            {
                EntityMetaDataComponent& metaData{ entity.GetComponent<EntityMetaDataComponent>() };

                data["Components"] = nlohmann::json::array();
                nlohmann::json& componentListNode{ data["Components"] };

                u32 index{ 0 };
                for (const TypeInfo* type : metaData.OwnedComponentTypes)
                {
                    if (const ComponentDescriptor* desc = ComponentDescriptorRegistry::Get().GetComponentDescriptorForType(*type))
                    {
                        void* componentAddress{ desc->GetComponentAddress(entity) };

                        componentListNode[index] = nlohmann::json::object();
                        nlohmann::json& componentDataNode{ componentListNode[index] };
                        ++index;

                        auto saveFunction
                        {
                            [componentAddress, &componentDataNode](const PropertyInfo& propertyInfo)
                            {
                                SaveDataProperty(componentAddress, propertyInfo, componentDataNode);
                            }
                        };

                        componentDataNode["TypeID"] = type->GetTypeID();

                        type->ForEachProperty(saveFunction);
                    }
                }
            }

            void SaveWorld(const World& world, nlohmann::json& data)
            {
                data["Name"] = world.GetName();
                data["Entities"] = nlohmann::json::array();

                nlohmann::json& entityListNode{ data["Entities"] };

                u32 index{ 0 };
                world.ForEachEntity(
                    [&entityListNode, &index](Entity entity)
                    {
                        SaveEntity(entity, entityListNode[index]);
                        ++index;
                    }
                );
            }

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

            static void LoadEntity(Entity& entity, const nlohmann::json& data)
            {
                for (const nlohmann::json& componentDataNode : data["Components"])
                {
                    TypeID componentTypeID{ componentDataNode["TypeID"].get<TypeID>() };
                    if (const TypeInfo* typeInfo = ReflectedTypeRegistry::Get().FindTypeInfo(componentTypeID))
                    {
                        if (const ComponentDescriptor* desc = ComponentDescriptorRegistry::Get().GetComponentDescriptorForType(*typeInfo))
                        {
                            if (!desc->EntityHasComponent(entity))
                            {
                                desc->AddComponentToEntity(entity);
                            }
                            void* componentAddress{ desc->GetComponentAddress(entity) };

                            auto loadFunction
                            {
                                [componentAddress, &componentDataNode](const PropertyInfo& propertyInfo)
                                {
                                    LoadDataProperty(componentAddress, propertyInfo, componentDataNode);
                                }
                            };
                            typeInfo->ForEachProperty(loadFunction);
                        }
                        else
                        {
                            //Error
                        }
                    }
                    else
                    {
                        //Error
                    }
                }
            }

            static void LoadWorld(World& world, const nlohmann::json& data)
            {
                world.SetName(data["Name"].get<std::string>());

                world.ClearAllEntities();
                for (const nlohmann::json& entityData : data["Entities"])
                {
                    Entity entity{ world.CreateEntity() };
                    LoadEntity(entity, entityData);
                }
            }
        }

        void SaveUniverse(const Universe& universe, const std::string& filePath)
        {

        }

        void SaveWorld(const World& world)
        {
            nlohmann::json data;
            Internal::SaveWorld(world, data);
            
            std::string filePath{ "Assets/Worlds/" + world.GetName() + ".json" };

            std::ofstream outFile{ filePath };
            outFile << std::setw(4) << data;
        }

        void LoadUniverse(Universe& universe, const std::string& filePath)
        {
            nlohmann::json data;

            std::ifstream inFile{ filePath };
            inFile >> data;

            // TODO: do we really want to load all worlds ?
            // Perhaps save the names at least ?

            //universe.DestroyAllWorlds();
            //for (const nlohmann::json& worldData : data)
            //{
            //    World* newWorld{ universe.CreateWorld() };
            //    LoadWorld(*newWorld, data["WorldName"].get<std::string>());
            //}
        }

        void LoadWorld(World& world, const std::string& worldName)
        {
            nlohmann::json data;

            std::string filePath{ "Assets/Worlds/" + worldName + ".json" };
            std::ifstream inFile{ filePath };
            inFile >> data;

            Internal::LoadWorld(world, data);
        }
    };
}