#pragma once

#include <poplin/core/types.hpp>
#include <poplin/core/singleton.hpp>
#include <poplin/engine/input/keycodes.hpp>
#include <poplin/engine/input/mousecodes.hpp>
#include <glm/glm.hpp>

namespace Poplin
{
    class Window;

    namespace Input
    {
        enum class EInputStates : u8
        {
            None = 0x00,
            DownState = 0x01,
            ChangeState = 0x02
        };

        class InputHandler : public Singleton<InputHandler>
        {
            friend class ApplicationWindow;

        public:
            InputHandler();
            ~InputHandler();

            EInputStates GetKeyStates(EKeyCode key) const;
            EInputStates GetMouseButtonStates(EMouseCode mouseButton) const;
            inline const glm::vec2 GetMousePosition() const { return m_MousePosition; }
            inline f32 GetMouseScroll() const { return m_MouseScroll; }

        private:
            void NotifyKeyStateChanged(EKeyCode key);
            void NotifyKeyDownState(EKeyCode key, bool state);
            void NotifyMouseButtonStateChanged(EMouseCode mouseButton);
            void NotifyMouseButtonDownState(EMouseCode mouseButton, bool state);
            void SetMousePosition(f32 mouseX, f32 mouseY);
            inline void SetMouseScroll(f32 scroll) { m_MouseScroll = scroll; }
            void ResetChangeStates();

            EInputStates m_KeyStates[static_cast<u32>(EKeyCode::Count)];
            EInputStates m_MouseButtonStates[static_cast<u32>(EMouseCode::Count)];
            glm::vec2 m_MousePosition;
            f32 m_MouseScroll;
        };
}
}