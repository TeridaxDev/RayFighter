#include "GameManager.h"

GameManager::GameManager()
{
	player1 = FGFighter();
}

GameManager::~GameManager()
{
}

void GameManager::Update()
{
	player1.FGUpdate();
}

void GameManager::Draw()
{
	player1.FGDraw();
	player1.FGDrawHitboxes();
}
