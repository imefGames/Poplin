#pragma once

#include <entt/entt.hpp>

#include <functional>

namespace Poplin
{
    class Entity;

    class EntityRegistry
    {
        friend class Entity;

    public:
        Entity CreateEntity();
        void ForEachEntity(const std::function<void(Entity)>& function) const;
        void ClearAllEntities();

        template <class ... Components>
        void ForEach(const std::function<void(Components&...)>& function)
        {
            entt::view<entt::exclude_t<>, Components...> view{ m_Registry.view<Components...>() };
            view.each(function);
        }

    private:
        entt::registry m_Registry;
    };
}