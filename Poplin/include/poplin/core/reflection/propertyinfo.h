#pragma once

#include <poplin/core/error.h>
#include <poplin/core/types.hpp>
#include <glm/glm.hpp>
#include <memory>
#include <string>

namespace Poplin
{
    using PropertyID = u64;

    enum class EPropertyType : u8
    {
        Unknown,

        Bool,
        U8,
        U16,
        U32,
        U64,
        S8,
        S16,
        S32,
        S64,
        F32,

        Vector2,
        Vector3,
        Vector4,

        String,

        TypeInstance,
        TypeInstancePointer
    };

    namespace PropertyUtils
    {
        template <typename T> static EPropertyType GetPropertyType(const T* b) { return EPropertyType::Unknown; }
        static EPropertyType GetPropertyType(const bool*) { return EPropertyType::Bool; }
        static EPropertyType GetPropertyType(const u8*) { return EPropertyType::U8; }
        static EPropertyType GetPropertyType(const u16*) { return EPropertyType::U16; }
        static EPropertyType GetPropertyType(const u32*) { return EPropertyType::U32; }
        static EPropertyType GetPropertyType(const u64*) { return EPropertyType::U64; }
        static EPropertyType GetPropertyType(const s8*) { return EPropertyType::S8; }
        static EPropertyType GetPropertyType(const s16*) { return EPropertyType::S16; }
        static EPropertyType GetPropertyType(const s32*) { return EPropertyType::S32; }
        static EPropertyType GetPropertyType(const s64*) { return EPropertyType::S64; }
        static EPropertyType GetPropertyType(const f32*) { return EPropertyType::F32; }
        static EPropertyType GetPropertyType(const glm::vec2*) { return EPropertyType::Vector2; }
        static EPropertyType GetPropertyType(const glm::vec3*) { return EPropertyType::Vector3; }
        static EPropertyType GetPropertyType(const glm::vec4*) { return EPropertyType::Vector4; }
        static EPropertyType GetPropertyType(const std::string*) { return EPropertyType::String; }
        template <class T> static EPropertyType GetPropertyType(const std::shared_ptr<T>*) { return EPropertyType::TypeInstancePointer; }
    }

    enum class EPropertyVisibility : u8
    {
        Public,
        Private,
        Protected
    };

    class PropertyAccessor
    {
    public:
        virtual void* GetPropertyAddress(void* typeAddress) const = 0;
        virtual void SetPropertyAddress(void* typeAddress, const void* newValue) const = 0;
    };

    template <class Type, class PropertyType>
    class PropertyAccessorImpl : public PropertyAccessor
    {
        using PropertyAccessorGetter = PropertyType& (*)(Type&);
        using PropertyAccessorSetter = void (*)(Type&, const PropertyType&);

    public:
        PropertyAccessorImpl(PropertyAccessorGetter getter, PropertyAccessorSetter setter)
            : m_Getter{ getter }
            , m_Setter{ setter }
        {
        }

        void* GetPropertyAddress(void* typeAddressRaw) const override
        {
            Type* typeAddress{ reinterpret_cast<Type*>(typeAddressRaw) };
            return &(m_Getter(*typeAddress));
        }

        void SetPropertyAddress(void* typeAddressRaw, const void* newValueRaw) const override
        {
            Type* typeAddress{ reinterpret_cast<Type*>(typeAddressRaw) };
            const PropertyType* newValue{ reinterpret_cast<const PropertyType*>(newValueRaw) };
            m_Setter(*typeAddress, *newValue);
        }

    private:
        PropertyAccessorGetter m_Getter;
        PropertyAccessorSetter m_Setter;
    };

    class PropertyInfo
    {
    public:
        enum class Flags : u8
        {
            None = 0x00,
            IsEnum = 0x01,
            IsManagedAsset = 0x02,
        };

        PropertyInfo(PropertyID id, const char* name, u32 offset, EPropertyType type, EPropertyVisibility visibility, u64 specificID = 0, Flags flags = Flags::None, PropertyAccessor* propertyAccessor = nullptr);

        inline PropertyID GetID() const { return m_ID; }
        inline u64 GetSpecificID() const { return m_SpecificID; }
        inline const char* GetName() const { return m_Name; }
        inline u32 GetOffset() const { return m_Offset; }
        inline EPropertyType GetType() const { return m_Type; }
        inline EPropertyVisibility GetVisibility() const { return m_Visibility; }

        inline bool IsAnEnum() const { return (u8)m_Flags & (u8)Flags::IsEnum; }
        inline bool IsAManagedAsset() const { return (u8)m_Flags & (u8)Flags::IsManagedAsset; }

        template <class T>
        T* GetPropertyAddressAs(void* typeAddress) const
        {
            T* propertyPtr{ (T*)GetPropertyAddress(typeAddress) };
            PoplinWarning(PropertyUtils::GetPropertyType(propertyPtr) == m_Type, "Requested Property type does not match info.");
            return propertyPtr;
        }

        template <class T>
        void SetPropertyAddressAs(void* typeAddress, const T& newValue) const
        {
            PoplinWarning(PropertyUtils::GetPropertyType(&newValue) == m_Type, "Requested Property type does not match info.");
            return SetPropertyAddress(typeAddress, &newValue, sizeof(T));
        }

    private:
        void* GetPropertyAddress(void* typeAddress) const;
        void SetPropertyAddress(void* typeAddress, const void* newValue, u32 valueSize) const;

        PropertyID m_ID;
        const char* m_Name;
        u64 m_SpecificID;
        u32 m_Offset;
        EPropertyType m_Type;
        EPropertyVisibility m_Visibility;
        std::unique_ptr<PropertyAccessor> m_PropertyAccessor;
        Flags m_Flags;
    };
}