#pragma once

#include "livingEntity.h"
#include "soundManager.h"
#include "kinematicFlee.h"
#include "kinematicSeek.h"
#include "kinematicArrive.h"

class Bat: public LivingEntity{
public:
    static const string BAT_ANIM_FLAP;

    static const int BAT_STATE_IDLE;
    static const int BAT_STATE_MOVE;
    static const int BAT_STATE_DEAD;

    static const int BAT_AI_NORMAL;
    static const int BAT_AI_CHASE;

	int aiState = BAT_AI_NORMAL;

    float moveSpeedMax;

    LivingEntity* target = NULL;

    Bat(AnimationSet *animSet);
	void changeAnimation(int newState, bool resetFrameToBeginning);
    void update();
    void updateMovement(KinematicSteeringOutput steering);
    void updateAi();
    void move();
    void updateAnimation();
    void die();
    void updateDamages();
};
