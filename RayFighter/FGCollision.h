#pragma once

#include <raylib.h>

struct FGHitbox
{
	Rectangle rect;
	Vector2 velocity;
	bool null;

	static Rectangle WorldSpace(FGHitbox hitbox, Vector2 pos, float xOffset, float yOffset, bool reverse)
	{
		return Rectangle{ (reverse ? -hitbox.rect.x - hitbox.rect.width : hitbox.rect.x) + pos.x + xOffset, yOffset - (hitbox.rect.y + pos.y), hitbox.rect.width, hitbox.rect.height };
	}
};

struct FGHurtbox
{
	Rectangle rect;

	static Rectangle WorldSpace(FGHurtbox hurtbox, Vector2 pos, float xOffset, float yOffset, bool reverse)
	{
		return Rectangle{ (reverse ? -hurtbox.rect.x - hurtbox.rect.width : hurtbox.rect.x) + pos.x + xOffset, yOffset - (hurtbox.rect.y + pos.y), hurtbox.rect.width, hurtbox.rect.height };
	}

};

