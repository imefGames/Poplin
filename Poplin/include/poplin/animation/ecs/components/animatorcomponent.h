#pragma once

#include <poplin/core/reflection/typeinfo.h>
#include <poplin/engine/ecs/componentdescriptor.h>
#include <imgui/imgui.h>

namespace Poplin
{
    class AnimatorComponent
    {
    public:
        AnimatorComponent();

        f32 FrameElapsedTime;
        f32 TimePerFrame;
        u8 FrameCount;
        u8 CurrentFrame;
        u8 RowCount;
        u8 CurrentRow;
        bool IsPlaying;
        bool LoopFrames;
    };



    static const PropertyInfo g_AnimatorComponentPropertiesInfo[]
    {
        { 0, "Frame Elapsed Time", 0, EPropertyType::F32, EPropertyVisibility::Public },
        { 1, "Time Per Frame", 4, EPropertyType::F32, EPropertyVisibility::Public },
        { 2, "Frame Count", 8, EPropertyType::U8, EPropertyVisibility::Public },
        { 3, "Current Frame", 9, EPropertyType::U8, EPropertyVisibility::Public },
        { 4, "Row Count", 10, EPropertyType::U8, EPropertyVisibility::Public },
        { 5, "Current Row", 11, EPropertyType::U8, EPropertyVisibility::Public },
        { 6, "Is Playing", 12, EPropertyType::Bool, EPropertyVisibility::Public },
        { 7, "Loop Frames", 13, EPropertyType::Bool, EPropertyVisibility::Public }
    };
    static const TypeInfo g_AnimatorComponentTypeInfo
    (
        1432152,
        "Animator",
        sizeof(AnimatorComponent),
        g_AnimatorComponentPropertiesInfo,
        sizeof(g_AnimatorComponentPropertiesInfo) / sizeof(PropertyInfo),
        nullptr
    );

    namespace Reflection
    {
        template <>
        static const TypeInfo* GetTypeInfo<AnimatorComponent>()
        {
            return &g_AnimatorComponentTypeInfo;
        }
    }
}