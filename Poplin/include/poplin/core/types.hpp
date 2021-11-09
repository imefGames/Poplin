#pragma once

#include <limits>

namespace Poplin
{
    using Char = char;
    using u8  = unsigned char;
    using u16 = unsigned short;
    using u32 = unsigned long;
    using u64 = unsigned long long;
    using s8  = signed char;
    using s16 = signed short;
    using s32 = signed long;
    using s64 = signed long long;
    using f32 = float;

#pragma warning(push)
#pragma warning(disable : 4309)
    constexpr u8 u8Min{ std::numeric_limits<u8>::min() };
    constexpr u16 u16Min{ std::numeric_limits<u16>::min() };
    constexpr u32 u32Min{ std::numeric_limits<u32>::min() };
    constexpr u64 u64Min{ std::numeric_limits<u64>::min() };
    constexpr s8 s8Min{ std::numeric_limits<s8>::min() };
    constexpr s16 s16Min{ std::numeric_limits<s16>::min() };
    constexpr s32 s32Min{ std::numeric_limits<s32>::min() };
    constexpr s64 s64Min{ std::numeric_limits<s64>::min() };
    constexpr f32 f32Min{ std::numeric_limits<f32>::min() };

    constexpr u8 u8Max{ std::numeric_limits<u8>::max() };
    constexpr u16 u16Max{ std::numeric_limits<u16>::max() };
    constexpr u32 u32Max{ std::numeric_limits<u32>::max() };
    constexpr u64 u64Max{ std::numeric_limits<u64>::max() };
    constexpr s8 s8Max{ std::numeric_limits<s8>::max() };
    constexpr s16 s16Max{ std::numeric_limits<s16>::max() };
    constexpr s32 s32Max{ std::numeric_limits<s32>::max() };
    constexpr s64 s64Max{ std::numeric_limits<s64>::max() };
    constexpr f32 f32Max{ std::numeric_limits<f32>::max() };
#pragma warning(pop)
}