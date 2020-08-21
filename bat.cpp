#include "bat.h"

const string Bat::BAT_ANIM_FLAP = "flap";

const int Bat::BAT_STATE_IDLE = 0;
const int Bat::BAT_STATE_MOVE = 1;
const int Bat::BAT_STATE_DEAD = 2;


const int Bat::BAT_AI_NORMAL = 0;
const int Bat::BAT_AI_CHASE = 1;

Bat::Bat(AnimationSet *animSet){
    this->animSet = animSet;
    type = "enemy";

    x = Globals::ScreenWidth / 2;
	y = Globals::ScreenHeight / 2;

    moveSpeedMax = 10;
    moveSpeed = 0;
    hp = 1;

    collisionBoxW = 0;
	collisionBoxH = 0;
    collisionBox.w = collisionBoxW;
	collisionBox.h = collisionBoxH;

    collisionBoxYOffset = 0;
    changeAnimation(BAT_STATE_IDLE, true);
    updateCollisionBox();

}

void Bat::changeAnimation(int newState, bool resetFrameToBeginning){
    state = newState;

    currentAnim = animSet->getAnimation(BAT_ANIM_FLAP);
    if (resetFrameToBeginning)
		currentFrame = currentAnim->getFrame(0);
	else
		currentFrame = currentAnim->getFrame(currentFrame->frameNumber);
}


void Bat::update(){


	if (hp < 1 && state != BAT_STATE_DEAD){
		// changeAnimation(BAT_STATE_DEAD, true);
		moving = false;
		die();
	}
    updateAi();
    updateCollisionBox();
	updateCollisions();
    updateAnimation();


}

void Bat::updateAnimation(){
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

void Bat::updateAi(){
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
            aiState = BAT_AI_NORMAL;
        }
        else
        {
            //otherwise chase the player
            aiState = BAT_AI_CHASE;
        }
    }
    else
    {
        //no targets, go idle
        moving = false;
        aiState = BAT_AI_NORMAL;
        // changeAnimation(GLOB_STATE_IDLE, true);
    }

    	//if chasing a target, then do that
	if (aiState == BAT_AI_CHASE && hp > 0 && active && target != NULL){
	    KinematicArrive steerRequest(this, target);
        KinematicSteeringOutput steering = steerRequest.getSteering();
		move();
        updateMovement(steering);
	}

}

void Bat::updateMovement(KinematicSteeringOutput steering){
    updateCollisionBox();
    x += steering.velocity[0] * TimeController::timeController.dT;
    y += steering.velocity[1] * TimeController::timeController.dT;
	if (!moving)
		moveSpeed -= moveSpeed;
    updateCollisionBox();

}
void Bat::move(){
	moving = true;
	moveSpeed = moveSpeedMax;

}
void Bat::die(){
	moving = false;
	state = BAT_STATE_DEAD;
}
void Bat::updateDamages(){

}
	//add to our score coun