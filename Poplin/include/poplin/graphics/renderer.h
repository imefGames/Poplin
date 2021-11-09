#pragma once

#include <glm/glm.hpp>
#include <poplin/core/singleton.hpp>
#include <memory>

namespace Poplin
{
    class Shader;
    class SpriteComponent;
    class Texture;
    class VertexArray;

    class Renderer : public Singleton<Renderer>
    {
        friend class RenderSystem;

    public:
        Renderer();
        ~Renderer();

        void BeginFrame();
        void EndFrame();

        void DrawSprite(const glm::mat4& modelTransform, const SpriteComponent& sprite);

    private:
        glm::mat4 m_CameraView;
        glm::mat4 m_CameraProjection;
        std::shared_ptr<Texture> m_MissingTexture;
        std::shared_ptr<Shader> m_DefaultSpriteShader;
        std::shared_ptr<VertexArray> m_DefaultSpriteModel;
    };
}