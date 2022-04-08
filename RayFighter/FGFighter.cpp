#include "FGFighter.h"

#include <iostream>

//Const floats need to be initialized this way for some reason
const float FGFighter::groundLocationY = 80;
const float FGFighter::wallLocationX = 900;


void FGFighter::SetJoystick(Vector2 joy)
{
    if (joy.x == 0) joystick.x = 0;
    else if (joy.x > 0) joystick.x = 1;
    else joystick.x = -1;

    if (joy.y == 0) joystick.y = 0;
    else if (joy.y > 0) joystick.y = 1;
    else joystick.y = -1;
}

void FGFighter::SetButtons(unsigned char byte)
{
    /*
    Bindings:
    A - jump 0001
    X - poke 0010
    B - spike 0100
    Y - launch 1000
    */
    //Y5 B6 A7 X8 xbox format

    jump = ((byte & 0b0001) == 0b0001);
    poke = ((byte & 0b0010) == 0b0010);
    spike = ((byte & 0b0100) == 0b0100);
    launch = ((byte & 0b1000) == 0b1000);

    if (jump && _hitstop) bffJump = true;
    if (poke && _hitstop) bffPoke = true;
    if (spike && _hitstop) bffSpike = true;
    if (launch && _hitstop) bffLaunch = true;

}

FGFighter::FGFighter()
{
	position = Vector2{ 0, groundLocationY };
	velocity = Vector2{ 0, 0 };

    //Saves some time in testing.
    actions.emplace("idle", FGAction::NewDefaultAction());

    CurrentAction(FAct("idle"));
    state = FGFighterState::idle;
}

FGFighter::~FGFighter()
{
    for (auto i : actions) delete i.second;
    actions.clear();
    _currentAction;
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
        velocity.x *= friction;
        velocity.y = 0;

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
        position = Vector2{ position.x + velocity.x, groundLocationY };
        velocity.x *= friction;

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

    CurrentAction()->FGAUpdate(*this);

    if (position.x > wallLocationX) position.x = wallLocationX;
    if (position.x < -wallLocationX) position.x = -wallLocationX;

    oldJoystick = joystick;
    oldJump = jump;
    oldPoke = poke;
    oldSpike = spike;
    oldLaunch = launch;
    if (bffJump || bffPoke || bffSpike || bffLaunch) bffPoke = bffSpike = bffLaunch = bffJump = false;
}
