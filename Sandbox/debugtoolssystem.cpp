#include "debugtoolssystem.h"

#include <imgui/imgui.h>
#include <poplin/core/error.h>
#include <poplin/core/reflection/reflectedtyperegistry.h>
#include <poplin/engine/gameenginestats.hpp>
#include <poplin/engine/asset/assetlocator.h>
#include <poplin/engine/ecs/componentdescriptor.h>
#include <poplin/engine/ecs/componentdescriptorregistry.h>
#include <poplin/engine/ecs/entity.h>
#include <poplin/engine/ecs/systemupdater.h>
#include <poplin/engine/ecs/universe.h>
#include <poplin/engine/ecs/world.h>
#include <poplin/engine/ecs/components/transformcomponent.h>


#include "serializer.h"

namespace Poplin
{
    DebugToolsSystem::DebugToolsSystem(SystemUpdater& updater)
        : System{ updater }
    {
        updater.RegisterSystemUpdate(this, &DebugToolsSystem::UpdateDebugTools);
    }

    void DebugToolsSystem::EditComponentProperty(void* componentAddress, const PropertyInfo& propertyInfo)
    {
        switch (propertyInfo.GetType())
        {
            case EPropertyType::Bool:
            {
                bool b{ *propertyInfo.GetPropertyAddressAs<bool>(componentAddress) };
                ImGui::Checkbox(propertyInfo.GetName(), &b);
                propertyInfo.SetPropertyAddressAs(componentAddress, b);
                break;
            }
            case EPropertyType::U8:
            {
                u8 i{ *propertyInfo.GetPropertyAddressAs<u8>(componentAddress) };
                ImGui::DragScalar(propertyInfo.GetName(), ImGuiDataType_U8, &i, 1.0f);
                propertyInfo.SetPropertyAddressAs(componentAddress, i);
                break;
            }
            case EPropertyType::U16:
            {
                u16 i{ *propertyInfo.GetPropertyAddressAs<u16>(componentAddress) };
                ImGui::DragScalar(propertyInfo.GetName(), ImGuiDataType_U16, &i, 1.0f);
                propertyInfo.SetPropertyAddressAs(componentAddress, i);
                break;
            }
            case EPropertyType::U32:
            {
                if (propertyInfo.IsAnEnum())
                {
                    const EnumInfo* enumInfo{ ReflectedTypeRegistry::Get().FindEnumInfo(propertyInfo.GetSpecificID()) };

                    auto getEnumNames = [](void* data, int index, const char** text)
                    {
                        const EnumInfo::EnumEntry* entryList = (const EnumInfo::EnumEntry*)data;
                        *text = entryList[index].Name;
                        return true;
                    };

                    u32 selectedValue{ *propertyInfo.GetPropertyAddressAs<u32>(componentAddress) };

                    int comboSelectedItemIndex{ 0 };
                    for (int i = 0; i < enumInfo->GetValueCount(); ++i)
                    {
                        if (enumInfo->GetRawValues()[i].Value == selectedValue)
                        {
                            comboSelectedItemIndex = i;
                        }
                    }

                    int maxIndex{ (int)enumInfo->GetValueCount() };

                    ImGui::Combo(propertyInfo.GetName(), &comboSelectedItemIndex, getEnumNames, const_cast<EnumInfo::EnumEntry*>(enumInfo->GetRawValues()), maxIndex);

                    propertyInfo.SetPropertyAddressAs(componentAddress, enumInfo->GetRawValues()[comboSelectedItemIndex].Value);
                }
                else
                {
                    u32 i{ *propertyInfo.GetPropertyAddressAs<u32>(componentAddress) };
                    ImGui::DragScalar(propertyInfo.GetName(), ImGuiDataType_U32, &i, 1.0f);
                    propertyInfo.SetPropertyAddressAs(componentAddress, i);
                }
                break;
            }
            case EPropertyType::U64:
            {
                u64 i{ *propertyInfo.GetPropertyAddressAs<u64>(componentAddress) };
                ImGui::DragScalar(propertyInfo.GetName(), ImGuiDataType_U64, &i, 1.0f);
                propertyInfo.SetPropertyAddressAs(componentAddress, i);
                break;
            }
            case EPropertyType::S8:
            {
                s8 i{ *propertyInfo.GetPropertyAddressAs<s8>(componentAddress) };
                ImGui::DragScalar(propertyInfo.GetName(), ImGuiDataType_S8, &i, 1.0f);
                propertyInfo.SetPropertyAddressAs(componentAddress, i);
                break;
            }
            case EPropertyType::S16:
            {
                s16 i{ *propertyInfo.GetPropertyAddressAs<s16>(componentAddress) };
                ImGui::DragScalar(propertyInfo.GetName(), ImGuiDataType_S16, &i, 1.0f);
                propertyInfo.SetPropertyAddressAs(componentAddress, i);
                break;
            }
            case EPropertyType::S32:
            {
                s32 i{ *propertyInfo.GetPropertyAddressAs<s32>(componentAddress) };
                ImGui::DragScalar(propertyInfo.GetName(), ImGuiDataType_S32, &i, 1.0f);
                propertyInfo.SetPropertyAddressAs(componentAddress, i);
                break;
            }
            case EPropertyType::S64:
            {
                s64 i{ *propertyInfo.GetPropertyAddressAs<s64>(componentAddress) };
                ImGui::DragScalar(propertyInfo.GetName(), ImGuiDataType_S64, &i, 1.0f);
                propertyInfo.SetPropertyAddressAs(componentAddress, i);
                break;
            }
            case EPropertyType::F32:
            {
                f32 f{ *propertyInfo.GetPropertyAddressAs<f32>(componentAddress) };
                ImGui::DragFloat(propertyInfo.GetName(), &f, 0.025f);
                propertyInfo.SetPropertyAddressAs(componentAddress, f);
                break;
            }
            case EPropertyType::Vector2:
            {
                glm::vec2 v{ *propertyInfo.GetPropertyAddressAs<glm::vec2>(componentAddress) };
                ImGui::DragFloat2(propertyInfo.GetName(), &v[0], 0.025f);
                propertyInfo.SetPropertyAddressAs(componentAddress, v);
                break;
            }
            case EPropertyType::Vector3:
            {
                glm::vec3 v{ *propertyInfo.GetPropertyAddressAs<glm::vec3>(componentAddress) };
                ImGui::DragFloat3(propertyInfo.GetName(), &v[0], 0.025f);
                propertyInfo.SetPropertyAddressAs(componentAddress, v);
                break;
            }
            case EPropertyType::Vector4:
            {
                glm::vec4 v{ *propertyInfo.GetPropertyAddressAs<glm::vec4>(componentAddress) };
                ImGui::DragFloat4(propertyInfo.GetName(), &v[0], 0.025f);
                propertyInfo.SetPropertyAddressAs(componentAddress, v);
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
                    std::shared_ptr<ManagedAsset>* propertyPtr{ propertyInfo.GetPropertyAddressAs<std::shared_ptr<ManagedAsset>>(componentAddress) };

                    AssetID assetID{ *propertyPtr ? (*propertyPtr)->GetAssetID() : InvalidAssetID };
                    if (ImGui::InputScalar(propertyInfo.GetName(), ImGuiDataType_U64, &assetID))
                    {
                        std::shared_ptr<ManagedAsset> foundAsset{ AssetLocator::Get().FindAsset(assetID) };
                        *propertyPtr = foundAsset;
                    }
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

    void DebugToolsSystem::UpdateDebugTools(f32 deltaTime)
    {
        DisplayAssetsWindow();
        DisplayWorldWindow();

        ImGui::Begin("Engine Stats");
        ImGui::Text("DT: %f", GameEngineStats::Get().GetDeltaTime());
        ImGui::Text("FPS: %f", GameEngineStats::Get().GetFPS());
        ImGui::End();

        ImGui::Begin("Entity List");
        if (World* world = Universe::Get().GetCurrentWorld())
        {
            if (ImGui::Button("Add Empty Entity"))
            {
                Entity entity{ world->CreateEntity() };

                TransformComponent& transform{ entity.GetComponent<TransformComponent>() };
                transform.Position = { 0.5f, 0.5f, 0.0f };
                transform.Origin = { 0.5f, 0.5f, 0.0f };
            }

            world->ForEachEntity(
                [](Entity entity)
                {
                    ImGui::PushID(entity.GetEntityID());
                    if (ImGui::TreeNode("Entity"))
                    {
                        const ComponentDescriptor* componentToRemove{ nullptr };

                        EntityMetaDataComponent& metaData{ entity.GetComponent<EntityMetaDataComponent>() };
                        for (const TypeInfo* type : metaData.OwnedComponentTypes)
                        {
                            ImGui::PushID(type->GetTypeID()); //TODO: fix warning
                            if (const ComponentDescriptor* desc = ComponentDescriptorRegistry::Get().GetComponentDescriptorForType(*type))
                            {
                                bool hasComponent{ desc->EntityHasComponent(entity) };
                                if (hasComponent)
                                {
                                    if (ImGui::Button("X"))
                                    {
                                        componentToRemove = desc;
                                        hasComponent = false;
                                    }
                                    ImGui::SameLine();
                                }
                                if (ImGui::TreeNode(desc->GetName().c_str()))
                                {
                                    if (hasComponent)
                                    {
                                        if (const TypeInfo* componentTypeInfo = desc->GetComponentTypeInfo())
                                        {
                                            void* componentAddress{ desc->GetComponentAddress(entity) };
                                            auto editFunction
                                            {
                                                [componentAddress](const PropertyInfo& propertyInfo)
                                                {
                                                    if (propertyInfo.GetVisibility() == EPropertyVisibility::Public)
                                                        EditComponentProperty(componentAddress, propertyInfo);
                                                }
                                            };

                                            componentTypeInfo->ForEachProperty(editFunction);
                                        }
                                        else
                                        {
                                            PoplinWarning(false, "Failed to find Component Type Info.");
                                        }
                                    }
                                    ImGui::TreePop();
                                }
                            }
                            else
                            {
                                PoplinWarning(false, "Failed to find Component Type Info.");
                            }
                            ImGui::PopID();
                        }

                        if (componentToRemove != nullptr)
                        {
                            componentToRemove->RemoveComponentFromEntity(entity);
                        }


                        std::vector<ComponentDescriptor*> componentsToAdd{ ComponentDescriptorRegistry::Get().GetComponentDescriptors() };
                        auto removeOwned{ [&entity](const ComponentDescriptor* desc) { return desc->EntityHasComponent(entity); } };
                        auto newEndIt{ std::remove_if(componentsToAdd.begin(), componentsToAdd.end(), removeOwned) };
                        componentsToAdd.erase(newEndIt, componentsToAdd.end());

                        static int selectedIndex{ 0 };
                        int maxIndex{ (int)componentsToAdd.size() };
                        if (maxIndex > 0)
                        {
                            auto GetComponentComboNames = [](void* data, int index, const char** text)
                            {
                                ComponentDescriptor** componentList = (ComponentDescriptor**)data;
                                *text = componentList[index]->GetComponentTypeInfo()->GetTypeName();
                                return true;
                            };
                            

                            ImGui::Combo("Components", &selectedIndex, GetComponentComboNames, componentsToAdd.data(), maxIndex);

                            if (selectedIndex < (int)maxIndex && ImGui::Button("Add Component"))
                            {
                                componentsToAdd[selectedIndex]->AddComponentToEntity(entity);
                            }
                        }

                        ImGui::TreePop();
                    }
                    ImGui::PopID();
                }
            );
        }
        else
        {
            ImGui::Text("No world loaded.");
        }
        ImGui::End();
    }

    void DebugToolsSystem::DisplayAssetsWindow()
    {
        ImGui::Begin("Assets");
        for (const auto& assetPair : AssetLocator::Get().GetAllLoadedAssets())
        {
            ImGui::Text("%s: %s (ID: %d)", assetPair.second->GetTypeInfo()->GetTypeName(), assetPair.second->GetName().c_str(), assetPair.first);
        }
        ImGui::End();
    }

    void DebugToolsSystem::DisplayWorldWindow()
    {
        ImGui::Begin("World Properties");
        if (ImGui::Button("Save"))
        {
            World* world{ Universe::Get().GetCurrentWorld() };
            world->SetName(std::string("Test"));
            Serializer::SaveWorld(*world);
        }
        ImGui::SameLine();
        if (ImGui::Button("Load"))
        {
            World* world{ Universe::Get().GetCurrentWorld() };
            Serializer::LoadWorld(*world, std::string("Test"));
        }

        //TODO Gravity
        ImGui::End();
    }
}