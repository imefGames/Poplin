#include <poplin/physics/physicscontactlistener.h>

#include <poplin/physics/ecs/components/rigidbodycomponent.h>


#include <poplin/engine/asset/assetlocator.h>
#include <poplin/graphics/assets/textureasset.h>
#include <poplin/graphics/ecs/components/spritecomponent.h>

namespace Poplin
{
    void PhysicsContactListener::BeginContact(b2Contact* contact)
    {
        RigidBodyComponent::RigidBodyUserData* userDataA{ (RigidBodyComponent::RigidBodyUserData*)contact->GetFixtureA()->GetBody()->GetUserData().pointer };
        RigidBodyComponent::RigidBodyUserData* userDataB{ (RigidBodyComponent::RigidBodyUserData*)contact->GetFixtureB()->GetBody()->GetUserData().pointer };
    
        if (userDataA->m_Entity.HasComponent<SpriteComponent>())
        {
            SpriteComponent& sprite{ userDataA->m_Entity.GetComponent<SpriteComponent>() };
            if (sprite.SpriteTexture && sprite.SpriteTexture->GetAssetID() == 123)
            {
                sprite.SpriteTexture = std::dynamic_pointer_cast<TextureAsset>(AssetLocator::Get().FindAsset((AssetID)321));
            }
        }

        if (userDataB->m_Entity.HasComponent<SpriteComponent>())
        {
            SpriteComponent& sprite{ userDataB->m_Entity.GetComponent<SpriteComponent>() };
            if (sprite.SpriteTexture && sprite.SpriteTexture->GetAssetID() == 123)
            {
                sprite.SpriteTexture = std::dynamic_pointer_cast<TextureAsset>(AssetLocator::Get().FindAsset((AssetID)321));
            }
        }
    }

    void PhysicsContactListener::EndContact(b2Contact* contact)
    {
        RigidBodyComponent::RigidBodyUserData* userDataA{ (RigidBodyComponent::RigidBodyUserData*)contact->GetFixtureA()->GetBody()->GetUserData().pointer };
        RigidBodyComponent::RigidBodyUserData* userDataB{ (RigidBodyComponent::RigidBodyUserData*)contact->GetFixtureB()->GetBody()->GetUserData().pointer };

        if (userDataA->m_Entity.HasComponent<SpriteComponent>())
        {
            SpriteComponent& sprite{ userDataA->m_Entity.GetComponent<SpriteComponent>() };
            if (sprite.SpriteTexture && sprite.SpriteTexture->GetAssetID() == 321)
            {
                sprite.SpriteTexture = std::dynamic_pointer_cast<TextureAsset>(AssetLocator::Get().FindAsset((AssetID)123));
            }
        }

        if (userDataB->m_Entity.HasComponent<SpriteComponent>())
        {
            SpriteComponent& sprite{ userDataB->m_Entity.GetComponent<SpriteComponent>() };
            if (sprite.SpriteTexture && sprite.SpriteTexture->GetAssetID() == 321)
            {
                sprite.SpriteTexture = std::dynamic_pointer_cast<TextureAsset>(AssetLocator::Get().FindAsset((AssetID)123));
            }
        }
    }
}