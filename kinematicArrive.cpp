#include "kinematicArrive.h"

KinematicArrive::KinematicArrive(Entity *e1, Entity *e2){
    character = e1; 
    target = e2;
}

KinematicSteeringOutput KinematicArrive::getSteering(){
    KinematicSteeringOutput result;
    float vecLength = Entity::distanceBetweenTwoEntities(character, target);
    //If character is in target radius, don't have any velocity
    if (vecLength<radius){
        result.velocity.push_back(0);
        result.velocity.push_back(0);
        result.rotation = 0;
        return result;
    }

    maxSpeed = 30;

    float x = target->x - character->x;
    float y = target->y - character->y;
    result.velocity.push_back(x);
    result.velocity.push_back(y);

 
    for(auto &v : result.velocity){
        v /= timeToTarget;
    }

    if (vecLength > maxSpeed)
    {
        // float m = mag(result.velocity);
        // normalizeToMaxSpeed(result.velocity, m);
        float magnitude = sqrt(pow(result.velocity[0], 2) + pow(result.velocity[1], 2));
        if (magnitude > 0)
        {
            //stops dividing by zero
            for (auto &v : result.velocity)
            {
                v /= magnitude; //normalize
                v *= maxSpeed;  //vector coordinate * max
            }
        }
    }
    

    //TODO: setup orientation on enamies
    std::cout<<result.velocity[0]<< " "<< result.velocity[1] << endl;

    result.rotation = 0;

    return result;



}