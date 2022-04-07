#include "FGRenderer.h"

void FGRenderer::Draw()
{
}

void FGRenderer::DrawHitboxes()
{
	Vector2 pos = player->GetPosition();
	FGAction* act = player->CurrentAction();
	const std::vector<FGHurtbox>* hurtboxes = act->CurrentHurt();
	const std::vector<FGHitbox>* hitboxes = act->CurrentHit();
	bool reverse = player->GetFacingLeft();

	//Put 0 at the center of the screen so Wall coordinates can be symmetrical
	float xOffset = GetScreenWidth() / 2;
	//Raylib is Y-inverted (positive is down, ranges 0-screenHeight) and I want my coordinate system to have positive Y point up.
	float yOffset = GetScreenHeight();
	//We need to do the exact same math on collision detection

	for (auto i : *hurtboxes)
	{
		DrawRectangleRec(FGHurtbox::WorldSpace(i, pos, xOffset, yOffset, reverse), Color{0,0,255, 100});
	}

	for (auto i : *hitboxes)
	{
		if (!i.null)
		{
			DrawRectangleRec(FGHitbox::WorldSpace(i, pos, xOffset, yOffset, reverse), Color{255,0,0, 100});
		}
	}

	DrawPixel(pos.x + xOffset, yOffset - pos.y, PINK);

}
