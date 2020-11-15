#include "arrive.h"

Arrive::Arrive(Entity *e1, Entity *e2)
{
    character = e1;
    target = e2;
    timeToTarget = 0.1;
}

SteeringOutput Arrive::getSteering(){
    SteeringOutput result;
    //targetX - characterX
    float direction_x = target->x - character->x;
    //targetY - characterY
    float direction_y = target->y - character->y;

    maxSpeed = character->moveSpeedMax;

    float distance = Entity::distanceBetweenTwoEntities(character, target);

    if (distance < targetRadius)
    {
        result.x = 0;
        result.y = 0;
        result.angular = 0;
        return result;
    }

    if(distance>slowRadius)
    {
        targetSpeed = maxSpeed;
    }else{
        targetSpeed = (maxSpeed * distance) / slowRadius;
    }

    float targetVelocity_x = direction_x;
    float targetVelocity_y = direction_y;

    //Normalize tragetVelocity
    float magnitude = sqrt(pow(targetVelocity_x, 2) + pow(targetVelocity_y, 2));
    if (magnitude > 0)
    {
        targetVelocity_x /= magnitude;
        targetVelocity_y /= magnitude;
    }
    targetVelocity_x *= targetSpeed; 
    targetVelocity_y *= targetSpeed;
    //Acceleration tries to get to the target velocity.
    result.x = targetVelocity_x - character->velocity_x;
    result.y = targetVelocity_y - character->velocity_y;
    result.x /= timeToTarget;
    result.y /= timeToTarget;
    //Check if the acceleration is too fast.

    result.angular = 0;
    return result;
    



}
