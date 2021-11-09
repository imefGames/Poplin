#include <poplin/graphics/ecs/systems/rendersystem.h>

#include <glm/gtc/matrix_transform.hpp>

#include <poplin/engine/ecs/systemupdater.h>
#include <poplin/engine/ecs/components/transformcomponent.h>
#include <poplin/graphics/renderer.h>
#include <poplin/graphics/ecs/components/cameracomponent.h>
#include <poplin/graphics/ecs/components/spritecomponent.h>

namespace Poplin
{
    RenderSystem::RenderSystem(SystemUpdater& updater)
        : System{ updater }
    {
        updater.RegisterSystemUpdate(this, &RenderSystem::UpdateCamera);
        updater.RegisterSystemUpdate(this, &RenderSystem::RenderSprite);
    }

    void RenderSystem::UpdateCamera(f32 deltaTime, TransformComponent& transform, CameraComponent& camera)
    {
        Renderer& renderer{ Renderer::Get() };

        glm::vec3 lookFrom{ transform.Position + glm::vec3(0, 0, 1) };
        glm::vec3 lookTo{ transform.Position};

        renderer.m_CameraProjection = camera.ComputeProjection();
        renderer.m_CameraView = glm::lookAt(lookFrom, lookTo, glm::vec3(0, 1, 0));
    }

    void RenderSystem::RenderSprite(f32 deltaTime, TransformComponent& transform, SpriteComponent& sprite)
    {
        Renderer::Get().DrawSprite(transform.ComputeGlobalTransform(), sprite);
    }
}