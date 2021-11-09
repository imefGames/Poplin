#pragma once

#include <poplin/core/singleton.hpp>
#include <poplin/core/types.hpp>
#include <vector>

namespace Poplin
{
    class ComponentDescriptor;
    class TypeInfo;

    class ComponentDescriptorRegistry : public Singleton<ComponentDescriptorRegistry>
    {
    public:
        ComponentDescriptorRegistry();
        ~ComponentDescriptorRegistry();

        const ComponentDescriptor* GetComponentDescriptorForType(const TypeInfo& typeInfo) const;
        inline const std::vector<ComponentDescriptor*>& GetComponentDescriptors() const { return m_ComponentDescriptors; }

    private:
        std::vector<ComponentDescriptor*> m_ComponentDescriptors;
    };
}