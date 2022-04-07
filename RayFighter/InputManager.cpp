#include "InputManager.h"

Vector2 InputManager::GetJoystick(int controller, bool analog)
{
    Vector2 val = Vector2{ 0,0 };

    if(controller == -1)
    {
        //Arrow keys
        IsKeyDown(KEY_UP) ? val.y = val.y + 1 : 0;
        IsKeyDown(KEY_RIGHT) ? val.x = val.x + 1 : 0;
        IsKeyDown(KEY_DOWN) ? val.y = val.y - 1 : 0;
        IsKeyDown(KEY_LEFT) ? val.x = val.x - 1 : 0;
    }
    else
    {
        //Dpad
        IsGamepadButtonDown(controller, 1) ? val.y = val.y + 1 : 0;
        IsGamepadButtonDown(controller, 2) ? val.x = val.x + 1 : 0;
        IsGamepadButtonDown(controller, 3) ? val.y = val.y - 1 : 0;
        IsGamepadButtonDown(controller, 4) ? val.x = val.x - 1 : 0;
    }
    return val;
}

unsigned char InputManager::GetButtons(int controller)
{
    unsigned char val = 0b0000;

    if (controller == -1)
    {
        IsKeyDown(KEY_Z) ? val |= 0b0010 : 0;
        IsKeyDown(KEY_X) ? val |= 0b0100 : 0;
        IsKeyDown(KEY_C) ? val |= 0b1000 : 0;
        IsKeyDown(KEY_SPACE) ? val |= 0b0001 : 0;
    }
    else
    {
        /*
        Bindings:
        A - jump 0001
        X - poke 0010
        B - spike 0100
        Y - launch 1000
        */
        //Y5 B6 A7 X8 xbox format
        IsGamepadButtonDown(controller, 5) ? val |= 0b1000 : 0;
        IsGamepadButtonDown(controller, 6) ? val |= 0b0100 : 0;
        IsGamepadButtonDown(controller, 7) ? val |= 0b0001 : 0;
        IsGamepadButtonDown(controller, 8) ? val |= 0b0010 : 0;
    }

    return val;
}
