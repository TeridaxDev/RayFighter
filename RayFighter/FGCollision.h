#pragma once

#include <raylib.h>

struct FGHitbox
{
	Rectangle rect;
	Vector2 velocity;
	bool null;
};

struct FGHurtbox
{
	Rectangle rect;
};

