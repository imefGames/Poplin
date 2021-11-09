#include <poplin/animation/ecs/components/animatorcomponent.h>

namespace Poplin
{
    AnimatorComponent::AnimatorComponent()
        : FrameElapsedTime{ 0.0f }
        , TimePerFrame{ 1.0f }
        , FrameCount{ 1 }
        , CurrentFrame{ 0 }
        , RowCount{ 1 }
        , CurrentRow{ 0 }
        , IsPlaying{ false }
        , LoopFrames{ false }
    {
    }
}