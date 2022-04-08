#pragma once

#include "../FGAction.h"

class ShotoSpike : public FGAction
{
public:

	ShotoSpike() : FGAction(44, false, 0)
	{
        hurtboxes[0].resize(2);
        hurtboxes[0][0] = FGHurtbox{ Rectangle{-30, 132, 75, 2}};
        hurtboxes[0][1] = FGHurtbox{ Rectangle{0, 40, 20, 40} };
        hurtboxes[1].resize(2);
        hurtboxes[1][0] = FGHurtbox{Rectangle{-30, 120, 75, 120}};
        hurtboxes[1][1] = FGHurtbox{ Rectangle{0, 40, 50, 40} };
        hurtboxes[2].resize(2);
        hurtboxes[2][0] = FGHurtbox{Rectangle{-30, 105, 75, 105}};
        hurtboxes[2][1] = FGHurtbox{ Rectangle{0, 40, 80, 40} };
        hurtboxes[3].resize(2);
        hurtboxes[3][0] = FGHurtbox{Rectangle{-30, 92, 75, 92}};
        hurtboxes[3][1] = FGHurtbox{ Rectangle{0, 40, 110, 40} };
        hurtboxes[4].resize(2);
        hurtboxes[4][0] = FGHurtbox{Rectangle{-30, 80, 75, 80}};
        hurtboxes[4][1] = FGHurtbox{ Rectangle{0, 40, 150, 40} };
        hurtboxes[5].resize(2);
        hurtboxes[5][0] = FGHurtbox{Rectangle{-30, 66, 75, 66}};
        hurtboxes[5][1] = FGHurtbox{Rectangle{0, 40, 180, 40}};

        hitboxes[6].resize(2);
        hitboxes[6][0] = FGHitbox{ Rectangle{0, 33, 166, 33}, Vector2{1320, 200}, false };
        hitboxes[6][1] = FGHitbox{ Rectangle{0, 73, 56, 40}, Vector2{1320, 200}, false };
        hitboxes[10].resize(1);
        hitboxes[10][0] = hitboxes[6][0];
        hitboxes[25].resize(1);
        hitboxes[25][0] = FGHitbox{ Rectangle{}, Vector2{}, true };

        hurtboxes[43] = hurtboxes[0];
        hurtboxes[42] = hurtboxes[1];
        hurtboxes[41] = hurtboxes[2];
        hurtboxes[40] = hurtboxes[3];
        hurtboxes[39] = hurtboxes[4];
        hurtboxes[38] = hurtboxes[5];

	}

    void FGAUpdate(FGFighter& fighter) override
    {
        FGAction::FGAUpdate(fighter);

        if (frame >= 6 && frame < 25)
        {
            fighter.SetVelocity(Vector2{15.0f * (fighter.GetFacingLeft() ? -1 : 1), 0});
        }
        else if (frame >= 35)
        {
            fighter.SetVelocity(Vector2{5.2f * (fighter.GetFacingLeft() ? -1 : 1), 0});
        }
        else if (frame >= 30)
        {
            fighter.SetVelocity(Vector2{8.6f * (fighter.GetFacingLeft() ? -1 : 1), 0});
        }
        else if (frame >= 25)
        {
            fighter.SetVelocity(Vector2{15.2f * (fighter.GetFacingLeft() ? -1 : 1), 0});
        }


        fighter.SetPosition(Vector2{ fighter.GetPosition().x + fighter.GetVelocity().x, fighter.GetPosition().y});

    }

};