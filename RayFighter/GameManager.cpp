#include "GameManager.h"
#include "InputManager.h"

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
	//Vector2 val = InputManager::GetJoystick(controller1);
	if (IsGamepadButtonDown(0, 5))
	{
		GetGamepadName(0);
	}
	player1->SetJoystick(InputManager::GetJoystick(controller1));
	player1->SetButtons(InputManager::GetButtons(controller1));
	player1->FGUpdate();
	player2->SetJoystick(InputManager::GetJoystick(controller2));
	player2->SetButtons(InputManager::GetButtons(controller2));
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
