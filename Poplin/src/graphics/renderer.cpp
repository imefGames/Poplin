#include <poplin/graphics/renderer.h>

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <poplin/graphics/shader.h>
#include <poplin/graphics/texture.h>
#include <poplin/graphics/vertexarray.h>
#include <poplin/graphics/assets/textureasset.h>
#include <poplin/graphics/ecs/components/spritecomponent.h>
#include <poplin/graphics/loaders/modelloader.h>
#include <poplin/graphics/loaders/shaderloader.h>

namespace Poplin
{
    namespace Internal
    {
        void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
        {
            PoplinAssert(false, message);
        }
    }

    Renderer::Renderer()
    {
        RegisterInstance(this);

        glewExperimental = true; // Needed for core profile?

        GLenum initResult{ glewInit() };
        PoplinAssert(initResult == GLEW_OK, "Failed to init GLEW.");

        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(Internal::MessageCallback, 0);

        glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

        m_DefaultSpriteShader = ShaderLoader::LoadDefaultSpriteShader();
        m_DefaultSpriteModel = ModelLoader::MakeUnitSquare();

        u8 pixels[]
        {
            255, 0, 255
        };
        m_MissingTexture = std::make_shared<Texture>(pixels, 1, 1);

        //TODO: remove ?
        m_CameraProjection = glm::ortho(0.0f, 4.0f, 3.0f, 0.0f, 0.01f, 1000.0f);
        m_CameraView = glm::lookAt(
            glm::vec3(0, 0, 1),
            glm::vec3(0, 0, 0),
            glm::vec3(0, 1, 0));
    }

    Renderer::~Renderer()
    {
        UnregisterInstance(this);
    }

    void Renderer::BeginFrame()
    {
        glClear(GL_COLOR_BUFFER_BIT);

        m_DefaultSpriteShader->Bind();
        m_DefaultSpriteModel->Bind();
    }

    void Renderer::EndFrame()
    {
        m_DefaultSpriteModel->Unbind();
        m_DefaultSpriteShader->Unbind();
    }

    void Renderer::DrawSprite(const glm::mat4& modelTransform, const SpriteComponent& sprite)
    {
        glm::mat4 MVP = m_CameraProjection * m_CameraView * modelTransform;

        Texture* texture{ nullptr };
        if (sprite.SpriteTexture)
        {
            texture = sprite.SpriteTexture->Texture.get();
        }

        if (texture != nullptr)
        {
            texture->Bind();
        }
        else
        {
            m_MissingTexture->Bind();
        }
        m_DefaultSpriteShader->Bind();
        m_DefaultSpriteShader->SetValue("MVP", MVP);
        m_DefaultSpriteShader->SetValue("TextureSampler", 0L);
        m_DefaultSpriteShader->SetValue("UVRepeat", sprite.UVRepeat);
        m_DefaultSpriteShader->SetValue("UVOffset", sprite.UVOffset);

        glDrawArrays(GL_TRIANGLES, 0, m_DefaultSpriteModel->GetTriangleCount());
    }
}