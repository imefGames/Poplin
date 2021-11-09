#pragma once

#include <poplin/core/types.hpp>
#include <poplin/engine/input/keycodes.hpp>
#include <poplin/engine/input/mousecodes.hpp>
#include <glm/glm.hpp>

namespace Poplin
{
    namespace Input
    {
        bool IsKeyDown(EKeyCode key);
        bool IsKeyUp(EKeyCode key);
        bool IsKeyPressed(EKeyCode key);
        bool IsKeyReleased(EKeyCode key);

        glm::vec2 GetMousePosition();
        f32 GetMouseScroll();
        bool IsMouseButtonDown(EMouseCode mouseButton);
        bool IsMouseButtonUp(EMouseCode mouseButton);
        bool IsMouseButtonPressed(EMouseCode mouseButton);
        bool IsMouseButtonReleased(EMouseCode mouseButton);
    }
}