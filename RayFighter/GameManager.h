#pragma once

#include "FGFighter.h"

class GameManager
{
private:
	FGFighter player1, player2;

public:

	GameManager();
	~GameManager();

	void Update();

	void Draw();

};

