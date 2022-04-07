#pragma once

#include "FGCollision.h"

#include <vector>

class FGFighter; //Solves a circular #include reference

class FGAction
{
public:
    //I want these to be readonly, but I'm waiting until content complete to make a constructor
    std::vector<std::vector<FGHurtbox>> hurtboxes;          //both 2D arrays. outer layer = frame. inner layer = multiple hitboxes in one frame
    std::vector<std::vector<FGHitbox>> hitboxes;            //to avoid storing a lot of data, if any given frame has 0 data we go to the most recent frame with data.
    //std::vector<std::vector<Sprite>> sprites;              //The first sprite renders on bottom
    int duration;                    //in frames. measures the length of the move, not drawn animation frames (so you could animate at less than 60fps)
    bool looping;                    //Whether or not this action "ends" at lastFrame
    int loopFrame = 0;               //Which frame to return to at the end of a looping animation. default 0.
    Vector2 spriteOffset;

    int frame;
    bool ended = false;
    const std::vector<FGHurtbox>* CurrentHurt() const { return lastHurt; }
    const std::vector<FGHitbox>* CurrentHit() const { return lastHit; }
    //const Sprite* CurrentSprite() const { return lastSprite; }

private:
    std::vector<FGHurtbox>* lastHurt;           //These two variables are references to that "most recent frame" with data, to avoid looping through the array every frame.
    std::vector<FGHitbox>* lastHit;
    //Sprite* lastSprite;

public:

    FGAction(int duration, bool looping, int loopFrame = 0);
    
    virtual void FGAUpdate(FGFighter& fighter);
    //virtual void FGADraw(FGRenderer& renderer);
    //virtual void FGADrawHitboxes(FGRenderer& renderer);

    void SetActive();

    static FGAction NewDefaultAction();

};

