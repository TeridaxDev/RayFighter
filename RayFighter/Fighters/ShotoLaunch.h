#pragma once

#include "../FGAction.h"

class ShotoLaunch : public FGAction
{
public:
	
	ShotoLaunch() : FGAction(30, false, 0)
	{
        hurtboxes[0].resize(1);
        hurtboxes[0][0] = FGHurtbox{Rectangle{-30, 100, 75, 100 }};
        hurtboxes[2].resize(1);
        hurtboxes[2][0] = FGHurtbox{Rectangle{-30, 112, 75, 112}};
        hurtboxes[3].resize(1);
        hurtboxes[3][0] = FGHurtbox{Rectangle{-30, 118, 75, 118}};
        hurtboxes[4].resize(1);
        hurtboxes[4][0] = FGHurtbox{Rectangle{-30, 132, 75, 132}};


        hitboxes[2].resize(1);
        hitboxes[2][0] = FGHitbox{Rectangle{ -20, 145, 105, 105 }, Vector2{ 5000, 30000 }, false};
        hitboxes[4].resize(1);
        hitboxes[4][0] = FGHitbox{Rectangle{13, 160, 40, 80}, Vector2{3300, 18150}, false};
        hitboxes[14].resize(1);
        hitboxes[14][0] = FGHitbox{ Rectangle{}, Vector2{}, true };
	}

    void FGAUpdate(FGFighter& fighter) override
    {
        FGAction::FGAUpdate(fighter);

        if (frame == 4)
        {
            fighter.SetState(FGFighterState::airAttack);
            fighter.SetVelocity(Vector2{ 0.05f * (fighter.GetFacingLeft() ? -1 : 1), 0.55f});
        }
    }

};