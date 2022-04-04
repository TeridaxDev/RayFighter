#pragma once

#include <unordered_map>
#include <string>

#include "FGAction.h"
#include "FGRenderer.h"

enum class FGFighterState {
    intro, //intro animation??? skipping for now
    idle,
    run,
    crouch,
    air,
    attack,
    airAttack,
    jump, //jumpsquat, if any
    land, //landing lag
    hurt,
    dead
};

class FGFighter
{
protected:

    //consts
    const float groundLocationY = -17.62f; //TODO don't fucking do this
    const float wallLocationX = 11; //mirrored

    //Serialized Data
    std::unordered_map<std::string, FGAction> actions;
    float maxGroundSpeed;
    float maxAirSpeed; //horizontal
    float groundAcceleration;
    float friction;
    float airAcceleration;
    float gravity;
    float jumpVelocity;

    //State data
    Vector2 position, velocity; //coordinate system: x horizontal y vertical, positive is up & right
    FGFighterState state = FGFighterState::idle; //this is useful as a separate concept from currentAction, so we can do things like handle air drift the same regardless of if attacking or not.
    int cFrame; //current frame; how far along we are in a given action.
    int hitstopFrames; //if > 0, we skip updating that frame for visual/gamefeel reasons
    bool hit; //generally: whether the attack we used connected. Set to true when it's possible to cancel into an action
    bool facingLeft;

    //Rendering
    FGRenderer renderer;

    //Buttons and input
    Vector2 joystick; //Digital, values should be -1 0 or 1.
    Vector2 oldJoystick;
    bool poke;
    bool oldPoke;
    bool spike;
    bool oldSpike;
    bool launch;
    bool oldLaunch;
    bool jump;
    bool oldJump;

private:
    FGAction* _currentAction;
    bool _hitstop;

    //Hitstop buffer
    bool bffPoke;
    bool bffSpike;
    bool bffLaunch;
    bool bffJump;

public:

    //Passthroughs
    void CurrentAction(FGAction* action) { _currentAction = action; _currentAction->SetActive(); }
    FGAction* CurrentAction() { return _currentAction; }

    //This is for buffering things out of hitstop. I know, it's gross.
    //    public bool Hitstop
    //{
    //    get = > _hitstop;
    //    set = > _hitstop = value;
    //}


    FGFighter();

    virtual void FGUpdate();
    virtual void FGDraw() { CurrentAction()->FGADraw(renderer); }
    virtual void FGDrawHitboxes() { CurrentAction()->FGADrawHitboxes(renderer); }

};

