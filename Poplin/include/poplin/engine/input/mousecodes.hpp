#pragma once

namespace Poplin
{
    namespace Input
    {
        //Keycodes obtained from GLFW_MOUSE_XXX defines
        enum class EMouseCode
        {
            Button1 = 0,
            Button2 = 1,
            Button3 = 2,
            Button4 = 3,
            Button5 = 4,
            Button6 = 5,
            Button7 = 6,
            Button8 = 7,

            ButtonLeft = Button1,
            ButtonRight = Button2,
            ButtonMiddle = Button3,

            Count = 8
        };
    }
}