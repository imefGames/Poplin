#pragma once

namespace Poplin
{
    class SystemUpdater;

    class System
    {
    public:
        System(SystemUpdater& updater);
        virtual ~System();

    private:
        SystemUpdater& m_Updater;
    };
}