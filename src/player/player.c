#include <stdio.h>
#include "player.h"


void InitPlayer(Entity* player){
    player->size = (Vector2){20, 60};
    player->position = (Vector2){ (SCREEN_W / 2), (SCREEN_H - player->size.y) };
    player->color = RED;
    player->gravityMultiply = 1.0f;
    player->speed = 200.0f;
    player->jumpForce = -400.0f;
    player->jumpState = 0;
    player->onGround = 0;
    player->dashActive = 0;
    player->dashDistance = 150.0f;
    player->dashSpeed = 600.0f;
    player->dashStartPosition = (Vector2){0.0f};
    player->velocity = (Vector2){0.0f};
    player->acceleration = (Vector2){0.0f};
    player->direction = IDLE;
}

void DrawPlayer(Entity* player){
    DrawRectangle(
        player->position.x,
        player->position.y,
        player->size.x,
        player->size.y,
        player->color
    );
}

void HandleInput(Entity* player, float delta){

    // MOVEMENT
    if(IsKeyDown(KEY_D)) {
        player->direction = RIGHT;
        if(!player->dashActive) player->velocity.x = player->speed;
    }
    if(IsKeyDown(KEY_A)) {
        player->direction = LEFT;
        if(!player->dashActive) player->velocity.x = player->speed;
    }
    if(!player->dashActive && !IsKeyDown(KEY_D) && !IsKeyDown(KEY_A) && !IsKeyDown(KEY_W)){
        player->direction = IDLE;
        player->velocity.x = 0;
    }
    
    // JUMP
    if(IsKeyPressed(KEY_SPACE)){
        // double jump
        if(player->onGround == 0 && player->jumpState == 1){
            player->velocity.y = player->jumpForce + 50;
            player->jumpState = 2;
        }
        // single jump
        if(player->onGround && player->jumpState == 0){
            player->jumpState = 1;
            player->velocity.y = player->jumpForce;
            player->onGround = 0;
        }
    }

    //DASH
    if(
        (IsKeyPressed(KEY_LEFT_SHIFT) && !player->dashActive) &&
        (player->direction == LEFT || player->direction == RIGHT)
    ){
        player->dashActive = 1;
        player->dashStartPosition.x = player->position.x;
        player->velocity.x = player->dashSpeed;
        player->velocity.y = 0;
        return;
    } 

}


void UpdatePlayerPosition(Entity* player, float delta){
    switch(player->direction){
        case IDLE:
            break;
        case LEFT:
            player->position.x -= player->velocity.x * delta;
            if(player->dashActive && (player->position.x < (player->dashStartPosition.x - player->dashDistance))){
                player->dashActive = 0;
            }
            break;
        case RIGHT:
            player->position.x += player->velocity.x * delta;
            if(player->dashActive && (player->position.x > (player->dashStartPosition.x + player->dashDistance))){
                player->dashActive = 0;
            }
            break;
    }
    player->position.y += player->velocity.y * delta;
}