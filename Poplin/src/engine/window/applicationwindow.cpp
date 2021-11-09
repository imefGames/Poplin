#include <poplin/engine/window/applicationwindow.h>

#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <poplin/core/error.h>
#include <poplin/engine/window/applicationwindowevents.hpp>

#include "../input/inputhandler.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace Poplin
{
    ApplicationWindow::ApplicationWindow()
        : m_Window{ nullptr }
        , m_InputHandler{ std::make_unique<Input::InputHandler>() }
    {
        if (glfwInit())
        {
            glfwWindowHint(GLFW_SAMPLES, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //Needed for MacOS?
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            m_Window = glfwCreateWindow(1024, 768, "I made a window! :)", NULL, NULL);
            if (m_Window != nullptr)
            {
                glfwMakeContextCurrent(m_Window);
                glfwSetInputMode(m_Window, GLFW_STICKY_KEYS, GL_TRUE);

                glfwSetKeyCallback(m_Window, &ApplicationWindow::OnKeyStateChangedProc);
                glfwSetMouseButtonCallback(m_Window, &ApplicationWindow::OnMouseStateChangedProc);
                glfwSetScrollCallback(m_Window, &ApplicationWindow::OnMouseScrollProc);
                glfwSetWindowSizeCallback(m_Window, &ApplicationWindow::OnWindowSizeChanged);

                IMGUI_CHECKVERSION();
                ImGui::CreateContext();
                ImGuiIO& io = ImGui::GetIO(); (void)io;
                ImGui::StyleColorsDark();
                ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
                ImGui_ImplOpenGL3_Init();
            }
            else
            {
                glfwTerminate();
                PoplinAssert(false, "Failed to create GLFW Window.");
            }
        }
        else
        {
            PoplinAssert(false, "Failed to init GLFW.");
        }
    }

    ApplicationWindow::~ApplicationWindow()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwTerminate();
    }

    void ApplicationWindow::BeginFrame()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ApplicationWindow::EndFrame()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_Window);
    }

    void ApplicationWindow::PollEvents(ApplicationWindowEvents& windowEvents)
    {
        double mouseX;
        double mouseY;
        glfwGetCursorPos(m_Window, &mouseX, &mouseY);
        m_InputHandler->SetMousePosition(static_cast<f32>(mouseX), static_cast<f32>(mouseY));

        m_InputHandler->ResetChangeStates();

        glfwPollEvents();

        //TODO: remove
        windowEvents.ShouldCloseWindow = glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(m_Window);
    }

    void ApplicationWindow::OnKeyStateChangedProc(GLFWwindow* window, int key, int scanCode, int action, int mods)
    {
        if (action == GLFW_PRESS || action == GLFW_RELEASE)
        {
            Input::EKeyCode keyCode{ static_cast<Input::EKeyCode>(key) };
            Input::InputHandler& inputHandler{ Input::InputHandler::Get() };
            inputHandler.NotifyKeyDownState(keyCode, action == GLFW_PRESS);
            inputHandler.NotifyKeyStateChanged(keyCode);
        }
    }

    void ApplicationWindow::OnMouseStateChangedProc(GLFWwindow* window, int button, int action, int mods)
    {
        if (action == GLFW_PRESS || action == GLFW_RELEASE)
        {
            Input::EMouseCode mouseCode{ static_cast<Input::EMouseCode>(button) };
            Input::InputHandler& inputHandler{ Input::InputHandler::Get() };
            inputHandler.NotifyMouseButtonDownState(mouseCode, action == GLFW_PRESS);
            inputHandler.NotifyMouseButtonStateChanged(mouseCode);
        }
    }

    void ApplicationWindow::OnMouseScrollProc(GLFWwindow* window, double xOffset, double yOffset)
    {
        Input::InputHandler::Get().SetMouseScroll(static_cast<f32>(yOffset));
    }

    void ApplicationWindow::OnWindowSizeChanged(GLFWwindow* window, int width, int height)
    {
    }
}