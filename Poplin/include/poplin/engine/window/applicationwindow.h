#pragma once

#include <memory>

struct GLFWwindow;

namespace Poplin
{
    namespace Input
    {
        class InputHandler;
    }

    struct ApplicationWindowEvents;

    class ApplicationWindow
    {
    public:
        ApplicationWindow();
        ~ApplicationWindow();

        void BeginFrame();
        void EndFrame();
        void PollEvents(ApplicationWindowEvents& windowEvents);

    private:
        static void OnKeyStateChangedProc(GLFWwindow* window, int key, int scanCode, int action, int mods);
        static void OnMouseStateChangedProc(GLFWwindow* window, int button, int action, int mods);
        static void OnMouseScrollProc(GLFWwindow* window, double xOffset, double yOffset);
        static void OnWindowSizeChanged(GLFWwindow* window, int width, int height);

        std::unique_ptr<Input::InputHandler> m_InputHandler;
        GLFWwindow* m_Window;
    };
}