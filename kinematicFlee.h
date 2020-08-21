#pragma once

#include <SDL.h>
#include "entity.h"
#include "kinematicSteeringOutput.h"


class KinematicFlee{
    public:

        float maxSpeed;
   
        KinematicFlee(Entity *e1, Entity *e2);
        
        KinematicSteeringOutput getSteering();
        void normalize(std::vector<float>&, float&);
        float mag(std::vector<float>&);
    private:
        Entity* character;
        Entity* target;

};

