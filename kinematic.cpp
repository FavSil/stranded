#include "kinematic.h"

void Kinematic::normalizeToMaxSpeed(std::vector<float> &vec_input, float &magnitude){
    //normalize vector, ie create a unit vector. Then multiply by speed to get new velocity
    if (magnitude > 0) {
        //stops dividing by zero
        for(auto &v : vec_input){
            v /= magnitude; //normalize
            v *= maxSpeed; //vector coordinate * max

        }
    }
}

float Kinematic::mag(std::vector<float> &vec_input){
    //sqrt(vx*vx + vy*vy)
    return sqrt(pow(vec_input[0], 2) + pow(vec_input[1], 2));
}
