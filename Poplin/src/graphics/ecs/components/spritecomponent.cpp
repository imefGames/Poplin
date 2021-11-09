#include <poplin/graphics/ecs/components/spritecomponent.h>

#include <poplin/graphics/assets/textureasset.h>

namespace Poplin
{
    SpriteComponent::SpriteComponent()
        : SpriteTexture{}
        , UVRepeat{ 1.0f }
        , UVOffset{}
    {
    }
}