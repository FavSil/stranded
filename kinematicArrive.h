#pragma once

#include <SDL.h>
#include "entity.h"
#include "kinematic.h"

class KinematicArrive: public Kinematic{
    public:
        const float timeToTarget = 0.15;
        KinematicArrive(Entity*, Entity*);
        KinematicSteeringOutput getSteering();

    private:
        Entity *character;
        Entity *target;
        float maxSpeed;
        //TODO: make radius a required constructor parameter
        float radius = 50;

};