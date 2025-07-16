#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#define GRAVITY 890.0f

void ApplyGravity(Entity* entity, float deltaTime){
    if(!entity->dashActive || (!entity->dashActive && !entity->onGround)){
        entity->velocity.y += (GRAVITY * deltaTime) * entity->gravityMultiply;
    }
}

void DetectCollision(Entity* entity){
    // GROUND
    if(entity->position.y >= SCREEN_H - entity->size.y){
        entity->position.y = SCREEN_H - entity->size.y;
        entity->velocity.y = 0;
        entity->onGround = 1;
        entity->jumpState = 0;
    }
}