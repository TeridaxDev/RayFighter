#include "FGAction.h"

#include "FGFighter.h"

FGAction::FGAction(int duration, bool looping, int loopFrame) : duration{duration}, looping{looping}, loopFrame{loopFrame}, spriteOffset{0,0}
{
	hurtboxes.resize(duration);
	hitboxes.resize(duration);
	//sprites.resize(duration);

    SetActive();
}

void FGAction::FGAUpdate(FGFighter& fighter)
{
    frame++;

    if (frame >= duration && looping)
        frame = loopFrame;
    else if (frame >= duration - 1 && !looping) //We need to flag "ended" in advance, because we can't/won't react to it until next frame
        ended = true;


    //Find the most recent hurtbox with any data
    if (hurtboxes[frame].size() != 0) lastHurt = hurtboxes[frame].data();
    if (hitboxes.size() != 0)
        if (hitboxes[frame].size() != 0) lastHit = hitboxes[frame].data();         //To signal the end of a hitbox, simply have an empty array at the given frame.
    //if (sprites != null)
    //    if (sprites[frame] != null) lastSprite = sprites[frame];
}

void FGAction::FGADraw(FGRenderer& renderer)
{
}

void FGAction::FGADrawHitboxes(FGRenderer& renderer)
{
}

void FGAction::SetActive()
{
	frame = -1;
	ended = false;
	lastHurt = hurtboxes[0].data();
	lastHit = hitboxes[0].data();
}

FGAction FGAction::NewDefaultAction()
{
	return FGAction(1,false);
}
