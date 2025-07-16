#pragma once
#include "raylib.h"

//#define SCREEN_W GetScreenWidth()
//#define SCREEN_H GetScreenHeight()
#define SCREEN_W 1920   
#define SCREEN_H 1080

enum DirectionState { LEFT, RIGHT, IDLE};

typedef struct Entity {
    Vector2 size;
    Vector2 position;
    Color color;
    float gravityMultiply;
    float speed;
    float jumpForce;
    int jumpState;
    int onGround;
    int dashActive;
    float dashDistance;
    float dashSpeed;
    Vector2 dashStartPosition;
    Vector2 velocity;
    Vector2 acceleration;
    enum DirectionState direction;
} Entity;


