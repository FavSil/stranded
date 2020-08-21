#include "seek.h"

Seek::Seek(Entity *e1, Entity *e2)
{
    character = e1;
    target = e2;
}
SteeringOutput Seek::getSteering(){
    SteeringOutput result;
    //targetX - characterX
    result.x = target->x - character->y;
    //targetY - characterY
    result.y = target->y - character->y;

  
    float magnitude = sqrt(pow(result.x, 2) + pow(result.y, 2));
    if (magnitude > 0)
    {
        //stops dividing by zero
            result.x /= magnitude;
            result.y /= magnitude; //normalize
            result.x *= maxAcceleration;
            result.y *= maxAcceleration;  //vector coordinate * max
       
    }

    result.angular = 0;
    return result;
}