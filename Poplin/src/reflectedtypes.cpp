#include <poplin/reflectedtypes.h>

#include <poplin/core/reflection/typeinfo.h>

#include <poplin/animation/ecs/components/animatorcomponent.h>
#include <poplin/engine/ecs/components/transformcomponent.h>
#include <poplin/graphics/ecs/components/cameracomponent.h>
#include <poplin/graphics/assets/textureasset.h>
#include <poplin/graphics/ecs/components/spritecomponent.h>
#include <poplin/physics/ecs/components/rigidbodycomponent.h>

namespace Poplin
{
    namespace Reflection
    {
        void RegisterEngineTypes(std::map<TypeID, const TypeInfo*>& types)
        {
            types[g_TextureAssetTypeInfo.GetTypeID()] = &g_TextureAssetTypeInfo;
            types[g_TransformComponentTypeInfo.GetTypeID()] = &g_TransformComponentTypeInfo;
            types[g_CameraComponentTypeInfo.GetTypeID()] = &g_CameraComponentTypeInfo;
            types[g_SpriteComponentTypeInfo.GetTypeID()] = &g_SpriteComponentTypeInfo;
            types[g_RigidBodyComponentTypeInfo.GetTypeID()] = &g_RigidBodyComponentTypeInfo;
            types[g_AnimatorComponentTypeInfo.GetTypeID()] = &g_AnimatorComponentTypeInfo;
        }

        void RegisterEngineEnums(std::map<EnumID, const EnumInfo*>& enums)
        {
            enums[g_RigidBodyTypeEnum.GetEnumID()] = &g_RigidBodyTypeEnum;
        }
    }
}