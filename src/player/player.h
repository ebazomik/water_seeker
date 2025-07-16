#pragma once
#include "raylib.h"
#include "game.h"

void InitPlayer(Entity* player);
void DrawPlayer(Entity* player);
void UpdatePlayerPosition(Entity* player, float delta);
void HandleInput(Entity* player, float delta);