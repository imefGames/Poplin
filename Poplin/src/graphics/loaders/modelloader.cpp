#include <poplin/graphics/loaders/modelloader.h>

#include <glm/glm.hpp>
#include <vector>

namespace Poplin::ModelLoader
{
    std::shared_ptr<VertexArray> MakeUnitSquare()
    {
        std::vector<glm::vec3> vertexBufferData;
        vertexBufferData.push_back(glm::vec3{ 0.0f, 1.0f, 0.0f });
        vertexBufferData.push_back(glm::vec3{ 1.0f, 1.0f, 0.0f });
        vertexBufferData.push_back(glm::vec3{ 1.0f, 0.0f, 0.0f });
        vertexBufferData.push_back(glm::vec3{ 0.0f, 1.0f, 0.0f });
        vertexBufferData.push_back(glm::vec3{ 1.0f, 0.0f, 0.0f });
        vertexBufferData.push_back(glm::vec3{ 0.0f, 0.0f, 0.0f });

        std::vector<glm::vec2> uvBufferData;
        uvBufferData.push_back(glm::vec2{ 0.0f, 1.0f });
        uvBufferData.push_back(glm::vec2{ 1.0f, 1.0f });
        uvBufferData.push_back(glm::vec2{ 1.0f, 0.0f });
        uvBufferData.push_back(glm::vec2{ 0.0f, 1.0f });
        uvBufferData.push_back(glm::vec2{ 1.0f, 0.0f });
        uvBufferData.push_back(glm::vec2{ 0.0f, 0.0f });

        std::shared_ptr<VertexBuffer> vertexBuffer{ std::make_shared<VertexBuffer>(vertexBufferData.data(), sizeof(glm::vec3) * vertexBufferData.size(), EShaderDataType::Float3) };
        std::shared_ptr<VertexBuffer> uvBuffer{ std::make_shared<VertexBuffer>(uvBufferData.data(), sizeof(glm::vec2) * uvBufferData.size(), EShaderDataType::Float2) };

        std::shared_ptr<VertexArray> meshVertexArray{ std::make_shared<VertexArray>() };
        meshVertexArray->AddVertexBuffer(vertexBuffer);
        meshVertexArray->AddVertexBuffer(uvBuffer);
        meshVertexArray->SetTriangleCount(static_cast<u32>(vertexBufferData.size())); //TODO: remove with index buffer

        return meshVertexArray;
    }
}