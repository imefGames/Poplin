#include <poplin/engine/ecs/components/transformcomponent.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>

namespace Poplin
{
    TransformComponent::TransformComponent()
        : Origin{}
        , Position{}
        , Rotation{}
        , Scale{ 1.0f }
    {
    }

    glm::mat4 TransformComponent::ComputeGlobalTransform() const
    {
        glm::mat4 translation{ glm::translate(glm::mat4{ 1.0f }, Position) };
        glm::mat4 rotation{ glm::orientate4(glm::radians(Rotation)) };
        glm::mat4 scale{ glm::scale(Scale) };
        glm::mat4 originOffset{ glm::translate(glm::mat4{ 1.0f }, -Origin) };

        return translation * rotation * scale * originOffset;
    }
}