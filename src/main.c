#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "game.h"
#include "levels.h"
#include "player.h"
#include "utils.h"

#define RAYTMX_IMPLEMENTATION
#include "raytmx.h"


int main() {
    // ------------------------------------------------------------------
    // Initialization
    // ------------------------------------------------------------------
    InitWindow(SCREEN_W, SCREEN_H, "Water seeker");
    //ToggleFullscreen();
    Entity player;
    InitPlayer(&player);

    Camera2D camera = { 0 };
    camera.zoom = 1.0f;
    camera.target.x = player.position.x;
    camera.target.y = player.position.y;
    camera.offset.x = SCREEN_W / 2.0f;
    camera.offset.y = SCREEN_H / 2.0f;
    camera.rotation = 0.0f;

    const char* tmxMap = "assets/maps/proto_level.tmx";
    TmxMap* map = LoadTMX(tmxMap);
    if (map == NULL) {
        TraceLog(LOG_ERROR, "Failed to load TMX \"%s\"", tmxMap);
    }

    SetTargetFPS(60);

    // ------------------------------------------------------------------
    // Main Game loop
    // ------------------------------------------------------------------
    while (!WindowShouldClose()) {
        // ------------------------------------------------------------------
        // Update
        // ------------------------------------------------------------------

        float deltaTime = GetFrameTime();
        HandleInput(&player, deltaTime);
        UpdatePlayerPosition(&player, deltaTime);
        ApplyGravity(&player, deltaTime);
        DetectCollision(&player);
        camera.target = player.position;

        // ------------------------------------------------------------------
        // Draw
        // ------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(WHITE);
            //DrawLevelTest();
            DrawPlayer(&player);
            // BeginMode2D(camera);
            //     DrawTMX(map, &camera, 0, 0, WHITE);
            //     DrawPlayer(&player);
            // EndMode2D();
            DrawFPS(10, 10);
            DrawText(TextFormat("Player X: %.1f", player.position.x), 10, 30, 20, RED);
            DrawText(TextFormat("Player Y: %.1f", player.position.y), 10, 50, 20, RED);
            DrawText(TextFormat("Camera X: %.1f", camera.target.x), 10, 90, 20, BLUE);
            DrawText(TextFormat("Camera X: %.1f", camera.target.y), 10, 110, 20, BLUE);
            DrawText(TextFormat("Dash LEFT: %.1f", (player.dashStartPosition.x - player.dashDistance)), 10, 150, 20, GREEN);
            DrawText(TextFormat("Dash RIGHT: %.1f", (player.dashStartPosition.x + player.dashDistance)), 10, 170, 20, GREEN);
            DrawText(TextFormat("Dash ACTIVE: %d", player.dashActive), 10, 190, 20, BLACK);
        EndDrawing();
    }


    // ------------------------------------------------------------------
    // Unload
    // ------------------------------------------------------------------
    //UnloadTMX(map);
    CloseWindow();
    return 0;
}