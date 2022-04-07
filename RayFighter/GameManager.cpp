#include "GameManager.h"

GameManager::GameManager()
{
	player1 = new FGFighter();
	render1 = new FGRenderer(player1);
	player2 = new FGFighter();
	render2 = new FGRenderer(player2);

	player1->SetPositionX(-400);
	player2->SetPositionX(400);

	player1->TurnAround(false);
	player2->TurnAround(true);

}

GameManager::~GameManager()
{
	delete player1;
}

void GameManager::Update()
{
	player1->FGUpdate();
	player2->FGUpdate();
}

void GameManager::Draw()
{
	DrawLine(0, GetScreenHeight() - 50, GetScreenWidth(), GetScreenHeight() - 50, BLACK);

	render1->Draw();
	render1->DrawHitboxes();
	render2->Draw();
	render2->DrawHitboxes();


}
