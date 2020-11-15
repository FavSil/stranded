#pragma once
#include "entity.h"
#include <SDL.h>
#include "steeringOutput.h"
class Arrive{

public:
    Entity *character;
    Entity *target;
    float maxAcceleration = 5;
    float targetRadius = 10.0;
    float slowRadius = 50.0;
    float timeToTarget;
    float targetSpeed;
    float maxSpeed;
    Arrive(Entity *, Entity *);
    SteeringOutput getSteering();
};