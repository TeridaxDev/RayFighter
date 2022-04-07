#pragma once

#include "raylib.h"
#include "FGFighter.h"

class FGRenderer
{
private:
	FGFighter* player;


public:

	FGRenderer(FGFighter* player) : player(player) {};

	void Draw();
	void DrawHitboxes();

};

