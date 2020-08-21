#pragma once
#include "entity.h"
#include <SDL.h>
#include "steeringOutput.h"
class Seek{

public:
    Entity *character;
    Entity *target;
    float maxAcceleration;
    Seek(Entity *, Entity *);
    SteeringOutput getSteering();
};