#pragma once

// Implementation based off http://simmesimme.github.io/tutorials/2015/09/20/signal-slot

#include <poplin/core/types.hpp>
#include <functional>
#include <map>

namespace Poplin
{
    using SlotID = u32;
    constexpr SlotID SlotID_Invalid = u32Max;

    template <class ... Args>
    class Signal
    {
    public:
        using SlotType = std::function<void(Args...)>;

        Signal()
            : m_CurrentSlotID{ 0 }
        {
        }

        SlotID Connect(const SlotType& slot)
        {
            m_Slots.insert(std::make_pair(++m_CurrentSlotID, slot));
            return m_CurrentSlotID;
        }

        template <class T>
        SlotID Connect(T* instance, void (T::* functionPointer)(Args...))
        {
            return Connect([=](Args... args) { (instance->*functionPointer)(args...); });
        }

        template <class T>
        SlotID Connect(T* instance, void (T::* functionPointer)(Args...) const)
        {
            return Connect([=](Args... args) { (instance->*functionPointer)(args...); });
        }

        void Disconnect(SlotID id)
        {
            m_Slots.erase(id);
        }

        void DisconnectAll()
        {
            m_Slots.clear();
        }

        void Emit(Args... arguments)
        {
            for (auto const& it : m_Slots)
            {
                it.second(std::forward<Args>(arguments)...);
            }
        }

    private:
        Signal(const Signal& other) = delete;
        Signal& operator=(const Signal& other) = delete;

        std::map<SlotID, SlotType> m_Slots;
        SlotID m_CurrentSlotID;
    };
}