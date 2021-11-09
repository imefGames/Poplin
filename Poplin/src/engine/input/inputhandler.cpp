#include "inputhandler.h"

#include <algorithm>

namespace Poplin
{
    namespace Input
    {
        InputHandler::InputHandler()
            : m_KeyStates{ EInputStates::None }
            , m_MouseButtonStates{ EInputStates::None }
            , m_MousePosition{ 0.0f, 0.0f }
            , m_MouseScroll{ 0.0f }
        {
            RegisterInstance(this);
        }

        InputHandler::~InputHandler()
        {
            UnregisterInstance(this);
        }

        EInputStates InputHandler::GetKeyStates(EKeyCode key) const
        {
            EInputStates states{ EInputStates::None };
            if ((u8)key < (u8)EKeyCode::Count)
            {
                states = m_KeyStates[(u8)key];
            }
            return states;
        }

        EInputStates InputHandler::GetMouseButtonStates(EMouseCode mouseButton) const
        {
            EInputStates states{ EInputStates::None };
            if ((u8)mouseButton < (u8)EMouseCode::Count)
            {
                states = m_MouseButtonStates[(u8)mouseButton];
            }
            return states;
        }

        void InputHandler::NotifyKeyStateChanged(EKeyCode key)
        {
            if ((u8)key < (u8)EKeyCode::Count)
            {
                m_KeyStates[(u8)key] = (EInputStates)((u8)m_KeyStates[(u8)key] | (u8)EInputStates::ChangeState);
            }
        }

        void InputHandler::NotifyKeyDownState(EKeyCode key, bool state)
        {
            if ((u8)key < (u8)EKeyCode::Count)
            {
                if (state)
                {
                    m_KeyStates[(u8)key] = (EInputStates)((u8)m_KeyStates[(u8)key] | (u8)EInputStates::DownState);
                }
                else
                {
                    m_KeyStates[(u8)key] = (EInputStates)(((u8)m_KeyStates[(u8)key]) & ~((u8)(EInputStates::DownState)));
                }
            }
        }

        void InputHandler::NotifyMouseButtonStateChanged(EMouseCode mouseButton)
        {
            if ((u8)mouseButton < (u8)EMouseCode::Count)
            {
                m_MouseButtonStates[(u8)mouseButton] = (EInputStates)((u8)m_MouseButtonStates[(u8)mouseButton] | (u8)EInputStates::ChangeState);
            }
        }

        void InputHandler::NotifyMouseButtonDownState(EMouseCode mouseButton, bool state)
        {
            if ((u8)mouseButton < (u8)EMouseCode::Count)
            {
                if (state)
                {
                    m_MouseButtonStates[(u8)mouseButton] = (EInputStates)((u8)m_MouseButtonStates[(u8)mouseButton] | (u8)EInputStates::DownState);
                }
                else
                {
                    m_MouseButtonStates[(u8)mouseButton] = (EInputStates)(((u8)m_MouseButtonStates[(u8)mouseButton]) & ~((u8)(EInputStates::DownState)));
                }
            }
        }

        void InputHandler::SetMousePosition(f32 mouseX, f32 mouseY)
        {
            m_MousePosition = glm::vec2{ mouseX, mouseY };
        }

        void InputHandler::ResetChangeStates()
        {
            for (EInputStates& state : m_KeyStates)
            {
                state = (EInputStates)(((u8)state) & ~((u8)(EInputStates::ChangeState)));
            }

            for (EInputStates& state : m_MouseButtonStates)
            {
                state = (EInputStates)(((u8)state) & ~((u8)(EInputStates::ChangeState)));
            }

            m_MouseScroll = 0.0f;
        }
    }
}