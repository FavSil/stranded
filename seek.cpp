#include "seek.h"

Seek::Seek(Entity *e1, Entity *e2)
{
    character = e1;
    target = e2;
}
SteeringOutput Seek::getSteering(){
    SteeringOutput result;
    //targetX - characterX
    result.x = target->x - character->x;
    //targetY - characterY
    result.y = target->y - character->y;

    
    float magnitude = sqrt(pow(result.x, 2) + pow(result.y, 2));
    //check to not dividie by zero
    maxAcceleration = 10;
    result.angular = 0;

    if (magnitude > 0)
    {
            result.x /= magnitude;
            result.y /= magnitude; //normalize
            result.x *= maxAcceleration;
            result.y *= maxAcceleration;  //vector coordinate * max
            return result;
    }
    result.x = 0;
    result.y = 0;
    return result;  

   
}