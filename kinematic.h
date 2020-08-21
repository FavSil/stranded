#pragma once
#include <SDL.h>
#include "vector"
#include "kinematicSteeringOutput.h"

class Kinematic{
    public:
        void normalizeToMaxSpeed(std::vector<float>&, float&);
        float mag(std::vector<float>&);
        float maxSpeed;
};