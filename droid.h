#pragma once
#include <cstdlib>

#include "livingEntity.h"
#include "soundManager.h"
#include "steeringOutput.h"
#include "seek.h"
#include "arrive.h"

class Droid: public LivingEntity{
public:
    static const string DROID_ANIM_HOVER;
    static const string DROID_ANIM_NORTH;
    static const string DROID_ANIM_NORTH_EAST;
    static const string DROID_ANIM_EAST;
    static const string DROID_ANIM_SOUTH_EAST;
    static const string DROID_ANIM_SOUTH;
    static const string DROID_ANIM_SOUTH_WEST;
    static const string DROID_ANIM_WEST;
    static const string DROID_ANIM_NORTH_WEST;

    static const int DROID_STATE_IDLE;
    static const int DROID_STATE_MOVE;
    static const int DROID_STATE_DEAD;

    static const int DROID_AI_NORMAL;
    static const int DROID_AI_CHASE;

    int aiState = DROID_AI_NORMAL;

    std::vector<float> position;
    float orientation;
    std::vector<float> velocity;
    float rotation;

    LivingEntity *target = NULL;
    Droid(AnimationSet *animSet);

    void changeAnimation(int newState, bool resetFrameToBeginning);
    void update();
    void updateMovement(SteeringOutput steering);
    void updateAi();
    void move();
    void updateAnimation();
    void die();
    void updateDamages();

};