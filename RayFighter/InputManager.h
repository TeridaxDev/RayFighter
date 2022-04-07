#pragma once

#include "raylib.h"

class InputManager
{
public:
	//Controller ID -1 == keyboard

	static Vector2 GetJoystick(int controller, bool analog = false);

	static unsigned char GetButtons(int controller);

};

