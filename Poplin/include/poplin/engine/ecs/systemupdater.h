#pragma once

#include <poplin/core/types.hpp>
#include <poplin/engine/ecs/entityregistry.h>
#include <vector>

namespace Poplin
{
    class System;

    class SystemUpdater
    {
    public:
        ~SystemUpdater();

        void UpdateSystems(f32 deltaTime, EntityRegistry& registry) const;

        template <class SystemType, class ... Components>
        void RegisterSystemUpdate(SystemType* caller, void (SystemType::*updateFunction)(f32, Components&...))
        {
            m_Updaters.push_back(new UpdaterImpl(caller, updateFunction));
        }

        void UnregisterAllSystemUpdates(System* caller);

    private:
        class Updater
        {
        public:
            virtual void Invoke(f32 deltaTime, EntityRegistry& registry) const = 0;
            virtual const System* GetCaller() const = 0;
        };

        template <class SystemType, class ... Components>
        class UpdaterImpl : public Updater
        {
        public:
            UpdaterImpl(SystemType* caller, void (SystemType::*updateFunction)(f32, Components&...))
                : m_Caller{ caller }
                , m_UpdateFunction{ updateFunction }
            {
            }

            void Invoke(f32 deltaTime, EntityRegistry& registry) const override
            {
                registry.ForEach<Components...>([deltaTime, this](Components&... components)
                    {
                        (m_Caller->*m_UpdateFunction)(deltaTime, components...);
                    });
            }

            const System* GetCaller() const override
            {
                return m_Caller;
            }

        private:
            SystemType* m_Caller;
            void (SystemType::*m_UpdateFunction)(f32, Components&...);
        };

        template <class SystemType>
        class UpdaterImpl<SystemType> : public Updater
        {
        public:
            UpdaterImpl(SystemType* caller, void (SystemType::*updateFunction)(f32))
                : m_Caller{ caller }
                , m_UpdateFunction{ updateFunction }
            {
            }

            void Invoke(f32 deltaTime, EntityRegistry& registry) const override
            {
                (m_Caller->*m_UpdateFunction)(deltaTime);
            }

            const System* GetCaller() const override
            {
                return m_Caller;
            }

        private:
            SystemType* m_Caller;
            void (SystemType::*m_UpdateFunction)(f32);
        };

        std::vector<Updater*> m_Updaters;
    };
}