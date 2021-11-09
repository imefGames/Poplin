#include "sandboxreflectedtypes.h"

#include "playerbehaviorcomponent.h"
#include "scrollmessagecomponent.h"

namespace Poplin
{
    namespace Reflection
    {
        void RegisterGameTypes(std::map<TypeID, const TypeInfo*>& types)
        {
            types[g_PlayerBehaviorComponentTypeInfo.GetTypeID()] = &g_PlayerBehaviorComponentTypeInfo;
            types[g_ScrollMessageComponentTypeInfo.GetTypeID()] = &g_ScrollMessageComponentTypeInfo;
        }

        void RegisterGameEnums(std::map<EnumID, const EnumInfo*>& enums)
        {

        }
    }
}