#include "FGFighter.h"

#include <iostream>

FGFighter::FGFighter()
{
	position = Vector2{ 0, groundLocationY };
	velocity = Vector2{ 0, 0 };

    //Saves some time in testing.
    actions.emplace("idle", FGAction::NewDefaultAction());
    actions.emplace("run", FGAction::NewDefaultAction());
    actions.emplace("crouch", FGAction::NewDefaultAction());
    actions.emplace("air", FGAction::NewDefaultAction());

    CurrentAction(&actions.find("idle")->second);
    state = FGFighterState::idle;
}

void FGFighter::FGUpdate()
{
    
}
