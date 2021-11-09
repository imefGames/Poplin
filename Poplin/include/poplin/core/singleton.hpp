#pragma once

#include <poplin/core/error.h>

namespace Poplin
{
    template <class T>
    class Singleton
    {
    public:
        static void RegisterInstance(T* instance)
        {
            PoplinAssert(ms_Instance == nullptr, "[Singleton] The singleton already has an instance.");
            ms_Instance = instance;
        }

        static void UnregisterInstance(T* instance)
        {
            PoplinAssert(ms_Instance == instance, "[Singleton] Trying to unregister the wrong instance.");
            ms_Instance = nullptr;
        }

        static bool IsValid() { return ms_Instance != nullptr; }
        static T& Get() { return *ms_Instance; }

    private:
        static T* ms_Instance;
    };

    template <class T>
    T* Singleton<T>::ms_Instance = nullptr;
}