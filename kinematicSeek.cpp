#include "kinematicSeek.h"


KinematicSeek::KinematicSeek(Entity *e1, Entity *e2)
    { 
    character = e1;
    target= e2;
    }

KinematicSteeringOutput KinematicSeek::getSteering(){
    KinematicSteeringOutput result;
    //speed of seek

    //TODO CHANGE TO CHARACTER SPEED
    maxSpeed = 40;

    //find difference in position vector
    float x = target->x - character->x;
    float y = target->y - character->y;
    
    result.velocity.push_back(x);
    result.velocity.push_back(y);

    //get magnitude of the vector for normalization
    float m = mag(result.velocity);
    normalize(result.velocity, m);

    //roation not used
    //TODO get angular momentom velocity to change position
    result.rotation= 0;

    //DEBUG **REMOVE
    // std::cout << result.velocity[0] <<" " << result.velocity[1] << endl;

    return result;

}
void KinematicSeek::normalize(std::vector<float> &vec_input, float &magnitude){
    //normalize vector, ie create a unit vector. Then multiply by speed to get new velocity
    if (magnitude > 0) {
        //stops dividing by zero
        for(auto &v : vec_input){
            v /= magnitude; //normalize
            v *= maxSpeed; //vector coordinate * max

        }
    }
}

float KinematicSeek::mag(std::vector<float> &vec_input){
    //sqrt(vx*vx + vy*vy)
    return sqrt(pow(vec_input[0], 2) + pow(vec_input[1], 2));
}

