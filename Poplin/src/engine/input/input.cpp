#include <poplin/engine/input/input.h>

#include "inputhandler.h"

namespace Poplin
{
    namespace Input
    {
        bool IsKeyDown(EKeyCode key)
        {
            u8 keyState{ (u8)InputHandler::Get().GetKeyStates(key) };
            return (keyState & (u8)EInputStates::DownState);
        }

        bool IsKeyUp(EKeyCode key)
        {
            u8 keyState{ (u8)InputHandler::Get().GetKeyStates(key) };
            return !(keyState & (u8)EInputStates::DownState);
        }

        bool IsKeyPressed(EKeyCode key)
        {
            u8 keyState{ (u8)InputHandler::Get().GetKeyStates(key) };
            return (!(keyState & (u8)EInputStates::DownState) && keyState & (u8)EInputStates::ChangeState);
        }

        bool IsKeyReleased(EKeyCode key)
        {
            u8 keyState{ (u8)InputHandler::Get().GetKeyStates(key) };
            return (keyState & (u8)EInputStates::DownState && keyState & (u8)EInputStates::ChangeState);
        }

        glm::vec2 GetMousePosition()
        {
            return InputHandler::Get().GetMousePosition();
        }

        f32 GetMouseScroll()
        {
            return InputHandler::Get().GetMouseScroll();
        }

        bool IsMouseButtonDown(EMouseCode mouseButton)
        {
            u8 buttonState{ (u8)InputHandler::Get().GetMouseButtonStates(mouseButton) };
            return (buttonState & (u8)EInputStates::DownState);
        }

        bool IsMouseButtonUp(EMouseCode mouseButton)
        {
            u8 buttonState{ (u8)InputHandler::Get().GetMouseButtonStates(mouseButton) };
            return (buttonState & (u8)EInputStates::DownState && buttonState & (u8)EInputStates::ChangeState);
        }

        bool IsMouseButtonPressed(EMouseCode mouseButton)
        {
            u8 buttonState{ (u8)InputHandler::Get().GetMouseButtonStates(mouseButton) };
            return (buttonState & (u8)EInputStates::DownState && buttonState & (u8)EInputStates::ChangeState);
        }

        bool IsMouseButtonReleased(EMouseCode mouseButton)
        {
            u8 buttonState{ (u8)InputHandler::Get().GetMouseButtonStates(mouseButton) };
            return (!(buttonState & (u8)EInputStates::DownState) && buttonState & (u8)EInputStates::ChangeState);
        }
    }
}