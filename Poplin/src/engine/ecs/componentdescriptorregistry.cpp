#include <poplin/engine/ecs/componentdescriptorregistry.h>

#include <poplin/animation/ecs/components/animatorcomponent.h>
#include <poplin/engine/ecs/componentdescriptor.h>
#include <poplin/engine/ecs/components/transformcomponent.h>
#include <poplin/graphics/ecs/components/cameracomponent.h>
#include <poplin/graphics/ecs/components/spritecomponent.h>
#include <poplin/physics/ecs/components/rigidbodycomponent.h>

namespace Poplin
{
    extern void RegisterExternalComponents(std::vector<ComponentDescriptor*>& components);

#ifdef POPLIN_EDITOR
    extern void RegisterEditorComponents(std::vector<ComponentDescriptor*>& components);
#endif //POPLIN_EDITOR

    ComponentDescriptorRegistry::ComponentDescriptorRegistry()
    {
        RegisterInstance(this);

        m_ComponentDescriptors.push_back(ComponentDescriptorUtils::CreateComponentDescriptor<AnimatorComponent>("Animator"));
        m_ComponentDescriptors.push_back(ComponentDescriptorUtils::CreateComponentDescriptor<CameraComponent>("Camera"));
        m_ComponentDescriptors.push_back(ComponentDescriptorUtils::CreateComponentDescriptor<RigidBodyComponent>("RigidBody"));
        m_ComponentDescriptors.push_back(ComponentDescriptorUtils::CreateComponentDescriptor<SpriteComponent>("Sprite"));
        m_ComponentDescriptors.push_back(ComponentDescriptorUtils::CreateComponentDescriptor<TransformComponent>("Transform"));

#ifdef POPLIN_EDITOR
        RegisterEditorComponents(m_ComponentDescriptors);
#endif //POPLIN_EDITOR

        RegisterExternalComponents(m_ComponentDescriptors);
    }

    ComponentDescriptorRegistry::~ComponentDescriptorRegistry()
    {
        UnregisterInstance(this);

        for (ComponentDescriptor* descriptor : m_ComponentDescriptors)
        {
            delete descriptor;
        }
        m_ComponentDescriptors.clear();
    }

    const ComponentDescriptor* ComponentDescriptorRegistry::GetComponentDescriptorForType(const TypeInfo& typeInfo) const
    {
        auto findByType{ [&typeInfo](const ComponentDescriptor* descriptor) { return descriptor->GetComponentTypeInfo()->GetTypeID() == typeInfo.GetTypeID(); } };
        auto foundIt{ std::find_if(m_ComponentDescriptors.begin(), m_ComponentDescriptors.end(), findByType) };
        return (foundIt != m_ComponentDescriptors.end() ? *foundIt : nullptr);
    }
}