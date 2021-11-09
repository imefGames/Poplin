#include <poplin/graphics/ecs/components/cameracomponent.h>

#include <glm/gtc/matrix_transform.hpp>

namespace Poplin
{
    CameraComponent::CameraComponent()
        : TopLeft{ 0.0f, 3.0f }
        , BottomRight{ 4.0, 0.0f }
        , Near{ 0.001f }
        , Far{ 1000.0f }
    {
    }

    glm::mat4 CameraComponent::ComputeProjection() const
    {
        return glm::ortho(TopLeft.x, BottomRight.x, TopLeft.y, BottomRight.y, Near, Far);
    }
}