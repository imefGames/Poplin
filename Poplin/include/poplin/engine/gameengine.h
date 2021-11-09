#pragma once

#include <poplin/core/reflection/reflectedtyperegistry.h>
#include <poplin/engine/gameengineconfig.hpp>
#include <poplin/engine/gameenginestats.hpp>
#include <poplin/engine/asset/assetlocator.h>
#include <poplin/engine/ecs/componentdescriptorregistry.h>
#include <poplin/engine/ecs/universe.h>
#include <poplin/engine/window/applicationwindow.h>
#include <poplin/graphics/renderer.h>

namespace Poplin
{
    class GameEngine
    {
    public:
        GameEngine(const GameEngineConfig& config);

        void RunGameLoop();

    private:
        ReflectedTypeRegistry m_ReflectedTypeRegistry;
        ComponentDescriptorRegistry m_ComponentRegistry;
        GameEngineConfig m_Config;
        GameEngineStats m_Stats;
        ApplicationWindow m_Window;
        Renderer m_Renderer;
        AssetLocator m_AssetLocator;
        Universe m_Universe;
    };
}