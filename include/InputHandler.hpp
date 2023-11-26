#pragma once

class InputHandler
{
    public:
        virtual ~InputHandler() = default;

        virtual void InputUp() = 0;
        virtual void InputDown() = 0;
        virtual void InputReturn() = 0;
        virtual void InputEscape() = 0;
};