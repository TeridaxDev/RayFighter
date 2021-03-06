#pragma once

#include "FGRenderer.h"

class GameManager
{
private:
	FGFighter* player1;
	FGFighter* player2;
	FGRenderer* render1;
	FGRenderer* render2;

	int controller1 = -1;
	int controller2 = 0;

public:

	GameManager();
	~GameManager();

	void Update();

	void Draw();

};

