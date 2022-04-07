#include "FGFighter.h"

#include <iostream>

#define FAct(s) &actions.find(s)->second

//Const floats need to be initialized this way for some reason
const float FGFighter::groundLocationY = 50;
const float FGFighter::wallLocationX = 500;


FGFighter::FGFighter()
{
	position = Vector2{ 0, groundLocationY };
	velocity = Vector2{ 0, 0 };

    //Saves some time in testing.
    actions.emplace("idle", FGAction::NewDefaultAction());
    actions.emplace("run", FGAction::NewDefaultAction());
    actions.emplace("crouch", FGAction::NewDefaultAction());
    actions.emplace("air", FGAction::NewDefaultAction());
    actions.emplace("hurt", FGAction::NewDefaultAction());

    CurrentAction(FAct("idle"));
    state = FGFighterState::idle;
}

void FGFighter::FGUpdate()
{
    if (CurrentAction()->ended)
    {
        if (state == FGFighterState::attack)
        {
            state = FGFighterState::idle;
            CurrentAction(FAct("idle"));
            hit = false;
        }
        else if (state == FGFighterState::airAttack)
        {
            state = FGFighterState::air;
            CurrentAction(FAct("air"));
            hit = false;
        }
    }


    switch (state)
    {
    case FGFighterState::idle:
    case FGFighterState::crouch:
        position = Vector2{ position.x + velocity.x, groundLocationY };
        velocity.x, velocity.y *= friction; //Can I do this??

        if (jump && !oldJump)
        {
            state = FGFighterState::air;
            CurrentAction(FAct("air"));
            velocity.x = maxAirSpeed * joystick.x;
            velocity.y = jumpVelocity;
        }
        else if ((poke && !oldPoke) || bffPoke)
        {
            state = FGFighterState::attack;
            CurrentAction(FAct("poke"));
        }
        else if ((spike && !oldSpike) || bffSpike)
        {
            state = FGFighterState::attack;
            CurrentAction(FAct("spike"));
        }
        else if ((launch && !oldLaunch) || bffLaunch)
        {
            state = FGFighterState::attack;
            CurrentAction(FAct("launch"));
        }
        else if (joystick.x == 1 && joystick.y != -1)
        {
            state = FGFighterState::run;
            CurrentAction(FAct("run"));
            facingLeft = false;
        }
        else if (joystick.x == -1 && joystick.y != -1)
        {
            state = FGFighterState::run;
            CurrentAction(FAct("run"));
            facingLeft = true;
        }
        else if (joystick.y == -1 && state != FGFighterState::crouch)
        {
            state = FGFighterState::crouch;
            CurrentAction(FAct("crouch"));
        }
        else if (joystick.y != -1 && state == FGFighterState::crouch)
        {
            state = FGFighterState::idle;
            CurrentAction(FAct("idle"));
        }

        break;
    case FGFighterState::run:
        velocity = Vector2{ facingLeft ? std::max(velocity.x - groundAcceleration, -maxGroundSpeed) : std::min(velocity.x + groundAcceleration, maxGroundSpeed), groundLocationY };
        position = Vector2{ position.x + velocity.x, groundLocationY };

        if (jump && !oldJump)
        {
            state = FGFighterState::air;
            CurrentAction(FAct("air"));
            velocity.x = maxAirSpeed * joystick.x;
            velocity.y = jumpVelocity;
        }
        else if ((poke && !oldPoke) || bffPoke)
        {
            state = FGFighterState::attack;
            CurrentAction(FAct("poke"));
        }
        else if ((spike && !oldSpike) || bffSpike)
        {
            state = FGFighterState::attack;
            CurrentAction(FAct("spike"));
        }
        else if ((launch && !oldLaunch) || bffLaunch)
        {
            state = FGFighterState::attack;
            CurrentAction(FAct("launch"));
        }
        else if (joystick.y == -1 && oldJoystick.y != -1)
        {
            state = FGFighterState::crouch;
            CurrentAction(FAct("crouch"));
        }
        else if ((!facingLeft && joystick.x != 1) || (facingLeft && joystick.x != -1))
        {
            state = FGFighterState::idle;
            CurrentAction(FAct("idle"));
        }
        break;

    case FGFighterState::air:
    case FGFighterState::airAttack:
    {
        float vel = velocity.x + (joystick.x * airAcceleration);
        if (vel > maxAirSpeed) vel = maxAirSpeed;
        if (vel < -maxAirSpeed) vel = -maxAirSpeed;
        velocity = Vector2{ vel, velocity.y - gravity };
        position = Vector2{ position.x + velocity.x, position.y + velocity.y };

        if (position.y <= groundLocationY)
        {
            state = FGFighterState::idle;
            position.y = groundLocationY;
            CurrentAction(FAct("idle"));
            hit = false;
        }
        else if (bffPoke || (poke && !oldPoke && (state == FGFighterState::air || hit)))
        {
            state = FGFighterState::airAttack;
            CurrentAction(FAct("airPoke"));
            hit = false;
        }
        else if (bffSpike || (spike && !oldSpike && (state == FGFighterState::air || hit)))
        {
            state = FGFighterState::airAttack;
            CurrentAction(FAct("airSpike"));
            hit = false;
        }
        else if (bffLaunch || (launch && !oldLaunch && (state == FGFighterState::air || hit)))
        {
            state = FGFighterState::airAttack;
            CurrentAction(FAct("airLaunch"));
            hit = false;
        }

        break;
    }
    case FGFighterState::attack:
        if (hit)
        {
            if ((jump && !oldJump) || bffJump)
            {
                state = FGFighterState::air;
                CurrentAction(FAct("air"));
                velocity.x = maxAirSpeed * joystick.x;
                velocity.y = jumpVelocity;
                hit = false;
            }
            else if ((poke && !oldPoke) || bffPoke)
            {
                state = FGFighterState::attack;
                CurrentAction(FAct("poke"));
                hit = false;
            }
            else if ((spike && !oldSpike) || bffSpike)
            {
                state = FGFighterState::attack;
                CurrentAction(FAct("spike"));
                hit = false;
            }
            else if ((launch && !oldLaunch) || bffLaunch)
            {
                state = FGFighterState::attack;
                CurrentAction(FAct("launch"));
                hit = false;
            }
        }
        break;
    }

    //CurrentAction()->FGAUpdate(*this);

    if (position.x > wallLocationX) position.x = wallLocationX;
    if (position.x < -wallLocationX) position.x = -wallLocationX;

    oldJoystick = joystick;
    oldJump = jump;
    oldPoke = poke;
    oldSpike = spike;
    oldLaunch = launch;
    if (bffJump || bffPoke || bffSpike || bffLaunch) bffPoke = bffSpike = bffLaunch = bffJump = false;
}
