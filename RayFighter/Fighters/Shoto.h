#pragma once

#include "../FGFighter.h"
#include "ShotoLaunch.h"
#include "ShotoSpike.h"

class Shoto : public FGFighter
{
public:

	Shoto() : FGFighter()
	{
        maxGroundSpeed = 15.32;
        maxAirSpeed = 13.9;
        groundAcceleration = 4.42f;
        friction = 0.65f;
        airAcceleration = 0.364f;
        jumpVelocity = 36;
        gravity = 2.67f;

        actions.emplace("run", FGAction::NewDefaultAction());
        actions.emplace("air", FGAction::NewDefaultAction());
        actions.emplace("hurt", FGAction::NewDefaultAction());

        actions.emplace("crouch", new FGAction(4, true, 3));
        FAct("crouch")->hurtboxes[0].resize(1);
        FAct("crouch")->hurtboxes[1].resize(1);
        FAct("crouch")->hurtboxes[2].resize(1);
        FAct("crouch")->hurtboxes[3].resize(1);
        FAct("crouch")->hurtboxes[0][0] = FGHurtbox{ Rectangle{-30, 120, 75, 120}};
        FAct("crouch")->hurtboxes[1][0] = FGHurtbox{ Rectangle{-30, 106, 75, 106}};
        FAct("crouch")->hurtboxes[2][0] = FGHurtbox{ Rectangle{-30, 92, 75, 92} };
        FAct("crouch")->hurtboxes[3][0] = FGHurtbox{ Rectangle{-30, 78, 75, 78}};

        actions.emplace("poke", new FGAction(18, false));
        FAct("poke")->hurtboxes[0].resize(1);
        FAct("poke")->hurtboxes[0][0] = FGHurtbox{ Rectangle{-30, 183, 75, 183}};
        FAct("poke")->hurtboxes[1].resize(2);
        FAct("poke")->hurtboxes[1][0] = FGHurtbox{ Rectangle{-30, 183, 75, 183}};
        FAct("poke")->hurtboxes[1][1] = FGHurtbox{ Rectangle{35, 128, 46, 46} };
        FAct("poke")->hurtboxes[8] = FAct("poke")->hurtboxes[0];
        FAct("poke")->hitboxes[3].resize(1);
        FAct("poke")->hitboxes[3][0] = FGHitbox{ Rectangle{0, 138, 86, 66}, Vector2{132, 264}, false };
        FAct("poke")->hitboxes[6].resize(1);
        FAct("poke")->hitboxes[6][0] = FGHitbox{ Rectangle{}, Vector2{}, true };

        actions.emplace("airPoke", new FGAction(*FAct("poke")));

        actions.emplace("launch", new ShotoLaunch());
        actions.emplace("airLaunch", new ShotoLaunch());

        actions.emplace("spike", new ShotoSpike());


        actions.emplace("airSpike", new FGAction(18, false));
        FAct("airSpike")->hurtboxes[0].resize(1);
        FAct("airSpike")->hurtboxes[0][0] = FGHurtbox{ Rectangle{-30, 183, 75, 183} };
        FAct("airSpike")->hitboxes[3].resize(1);
        FAct("airSpike")->hitboxes[3][0] = FGHitbox{ Rectangle{ 0, 53, 100, 120}, Vector2{50, -50}, false };
        FAct("airSpike")->hitboxes[6].resize(1);
        FAct("airSpike")->hitboxes[6][0] = FGHitbox{ Rectangle{}, Vector2{}, true };
	}
};