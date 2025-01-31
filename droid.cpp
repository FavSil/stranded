#include "droid.h"

const string Droid::DROID_ANIM_HOVER = "hover";
const string Droid::DROID_ANIM_NORTH = "north";
const string Droid::DROID_ANIM_NORTH_EAST = "north-east";
const string Droid::DROID_ANIM_EAST="east";
const string Droid::DROID_ANIM_SOUTH_EAST="south-east";
const string Droid::DROID_ANIM_SOUTH="south";
const string Droid::DROID_ANIM_SOUTH_WEST="south-west";
const string Droid::DROID_ANIM_WEST="west";
const string Droid::DROID_ANIM_NORTH_WEST="north-west";

const int Droid::DROID_STATE_IDLE = 0;
const int Droid::DROID_STATE_MOVE = 1;
const int Droid::DROID_STATE_DEAD = 2;

const int Droid::DROID_AI_NORMAL = 0;
const int Droid::DROID_AI_CHASE = 1;

float moveSpeedMax;
LivingEntity *target = NULL;

Droid::Droid(AnimationSet *animSet){

    this->animSet = animSet;
    type = "enemy";

    x = Globals::ScreenWidth / 2;
	y = Globals::ScreenHeight / 2;
	moveSpeed = 0;
	moveSpeedMax = 50;
    hp = 1;
    // velocity[0] = 0;
    velocity.push_back(0);
    velocity.push_back(0);
    rotation = 0;

    collisionBoxW = 0;
	collisionBoxH = 0;
    collisionBox.w = collisionBoxW;
	collisionBox.h = collisionBoxH;

    direction = DIR_DOWN;

    collisionBoxYOffset = 0;
    changeAnimation(DROID_STATE_IDLE, true);
    updateCollisionBox();

}

void Droid::changeAnimation(int newState, bool resetFrameToBeginning){
    state = newState;

    if (state == DROID_STATE_MOVE)
    {
        if (direction == DIR_DOWN)
            currentAnim = animSet->getAnimation(DROID_ANIM_SOUTH);
        if (direction == DIR_DOWN_RIGHT)
            currentAnim = animSet->getAnimation(DROID_ANIM_SOUTH_EAST);
        if (direction == DIR_RIGHT)
            currentAnim = animSet->getAnimation(DROID_ANIM_EAST);
        if (direction == DIR_UP_RIGHT)
            currentAnim = animSet->getAnimation(DROID_ANIM_NORTH_EAST);
        if (direction == DIR_UP)
            currentAnim = animSet->getAnimation(DROID_ANIM_NORTH);
        if (direction == DIR_UP_LEFT)
            currentAnim = animSet->getAnimation(DROID_ANIM_NORTH_WEST);
        if (direction == DIR_LEFT)
            currentAnim = animSet->getAnimation(DROID_ANIM_WEST);
        if (direction == DIR_DOWN_LEFT)
            currentAnim = animSet->getAnimation(DROID_ANIM_SOUTH_WEST);
        
    }
    else if (state == DROID_STATE_IDLE)
    {
        currentAnim = animSet->getAnimation(DROID_ANIM_HOVER);
    }
    else
    {
        currentAnim = animSet->getAnimation(DROID_ANIM_HOVER);
    }

    if (resetFrameToBeginning)
        currentFrame = currentAnim->getFrame(0);
    else
        currentFrame = currentAnim->getFrame(currentFrame->frameNumber);
}
void Droid::update(){

	if (hp < 1 && state != DROID_STATE_DEAD)
    {
		// changeAnimation(DROID_STATE_DEAD, true);
		moving = false;
		die();
	}

    updateAi();
    updateCollisionBox();
	updateCollisions();
    //CHANGE MADE
    updateAnimation();

}
void Droid::updateAi()
{
   target = NULL;
    for (auto entity = Entity::entities.begin(); entity != Entity::entities.end(); entity++){
		if ((*entity)->type == "hero" && (*entity)->active){
			//if found first hero in list, just set them as the target for now
			if (target == NULL){
				target = (LivingEntity*)(*entity); //if cant cast to LivingEntity, throw casting exception
			}
			else
			{
				//otherwise, is this other hero closer then the previous target
				if (Entity::distanceBetweenTwoEntities(this, (*entity)) < Entity::distanceBetweenTwoEntities(this, target))
				{
					target = (LivingEntity*)(*entity);
				}
			}
		}
	}

    //found a target and its alive, lets get 'em
    if (target != NULL && target->hp > 0)
    {
        float dist = Entity::distanceBetweenTwoEntities(this, target);
        //if in range, ATTACK!
        if (dist > 200)
        {
            aiState = DROID_AI_NORMAL;
        }
        else
        {
            //otherwise chase the player
            aiState = DROID_AI_CHASE;
        }
    }
    else
    {
        //no targets, go idle
        moving = false;
        aiState = DROID_AI_NORMAL;
    }

    if ( aiState == DROID_AI_CHASE && hp > 0 && target != NULL){

        Arrive  steerRequest(this, target);
        SteeringOutput steering = steerRequest.getSteering();
        move();
        updateMovement(steering);
    }

}
void Droid::updateMovement(SteeringOutput steering){ 
    updateCollisionBox();
    x += velocity_x * TimeController::timeController.dT;
    y += velocity_y * TimeController::timeController.dT;
    orientation += rotation * TimeController::timeController.dT;

    velocity_x += steering.x * TimeController::timeController.dT;
    velocity_y += steering.y * TimeController::timeController.dT;

    rotation += steering.angular * TimeController::timeController.dT;
    // std::cout<< steering.x << ' ' << steering.y;
    float magnitude = sqrt(pow(velocity[0], 2) + pow(velocity[1], 2));
    //check for speeding and clip
    if(magnitude > moveSpeedMax)
    {
        if (magnitude > 0)
        {
            //stops dividing by zero
            for (auto &v : velocity)
            {
                v /= magnitude; //normalize
                v *= moveSpeedMax;  //vector coordinate * max
            }
        }
    }
    if (!moving)
		moveSpeed -= moveSpeed;
    updateCollisionBox();
}
void Droid::move(){
	moving = true;
	moveSpeed = moveSpeedMax;
}
void Droid::updateAnimation(){
    if (currentFrame == NULL || currentAnim == NULL)
	    return;

	frameTimer += TimeController::timeController.dT;
    if(frameTimer >= currentFrame->duration){
        if(currentFrame->frameNumber == currentAnim->getEndFrameNumber()){
            currentFrame = currentAnim->getFrame(0);

        }else{
            currentFrame = currentAnim->getNextFrame(currentFrame);

        }
        frameTimer = 0;
    }
}
void Droid::die(){
	moving = false;
	state = DROID_STATE_DEAD;
}
void Droid::updateDamages(){

}

