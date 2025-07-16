#pragma once
#include "raylib.h"
#include "game.h"

void ApplyGravity(Entity* entity, float deltaTime);
void DetectCollision(Entity* entity);