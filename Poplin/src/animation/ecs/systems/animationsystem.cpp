#include <poplin/animation/ecs/systems/animationsystem.h>

#include <poplin/animation/ecs/components/animatorcomponent.h>
#include <poplin/engine/ecs/systemupdater.h>
#include <poplin/graphics/ecs/components/spritecomponent.h>

namespace Poplin
{
    AnimationSystem::AnimationSystem(SystemUpdater& updater)
        : System{ updater }
    {
        updater.RegisterSystemUpdate(this, &AnimationSystem::UpdateAnimation);
    }

    void AnimationSystem::UpdateAnimation(f32 deltaTime, AnimatorComponent& animator, SpriteComponent& sprite)
    {
        if (animator.IsPlaying)
        {
            animator.FrameElapsedTime += deltaTime;
            if (animator.FrameElapsedTime > animator.TimePerFrame)
            {
                animator.FrameElapsedTime -= animator.TimePerFrame;
                ++animator.CurrentFrame;
                if (animator.CurrentFrame >= animator.FrameCount)
                {
                    if (animator.LoopFrames)
                    {
                        animator.CurrentFrame %= animator.FrameCount;
                    }
                    else
                    {
                        animator.CurrentFrame = animator.FrameCount - 1;
                    }
                }
            }

            sprite.UVRepeat.x = 1.0f / animator.FrameCount;
            sprite.UVRepeat.y = 1.0f / animator.RowCount;

            sprite.UVOffset.x = static_cast<f32>(animator.CurrentFrame);
            sprite.UVOffset.y = static_cast<f32>(animator.CurrentRow);
        }
    }
}