#include "interface.h"
#include "raylib.h"

Texture2D background;

void interface_init(){
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT+40, "Snake Game");
    SetWindowIcon(LoadImage("assets/snake.png"));
    background = LoadTexture("assets/background.png");
    InitAudioDevice();
    SetTargetFPS(10);
}

void interface_draw(State state){
    if(state == NULL){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Game Over", SCREEN_WIDTH/2 - MeasureText("Game Over", 20)/2, SCREEN_WIDTH/2 - 20, 20, BLACK);
        EndDrawing();
        return;
    }
    StateInfo info = state_info(state);
    int Lives = info->lives;
    int Score = info->score;
    Vector snake = info->snake;
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexture(background, 0, 0, WHITE);
    DrawLine(0, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK);
    DrawText(TextFormat("Lives: %i", Lives), 10, SCREEN_HEIGHT + 10, 20, BLACK);
    DrawText(TextFormat("Score: %i", Score), SCREEN_WIDTH - MeasureText(TextFormat("Score: %i", Score), 20) - 10, SCREEN_HEIGHT + 10, 20, BLACK);
    for(int i = 0; i < vector_size(snake); i++){
        SnakeNode node = (SnakeNode)vector_get_at(snake, i);
        int x = get_x(node);
        int y = get_y(node);
        DrawRectangle(x, y%SCREEN_HEIGHT, SCALE, SCALE, BLACK);
    }
    DrawRectangle(info->foodx, info->foody, SCALE, SCALE, RED);
    if(info->is_paused){
        DrawText("Paused", SCREEN_WIDTH/2 - MeasureText("Paused", 20)/2, SCREEN_WIDTH/2 - 20, 20, BLACK);
    }
    EndDrawing();
    stateinfo_destroy(info);
}

void interface_close(){
    CloseWindow();
    CloseAudioDevice();
}