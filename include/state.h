#pragma once

#include <stdlib.h>
#include "ADTVector.h"
#include "Snake.h"
#include "raylib.h"

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500
#define SCALE 10

typedef struct state *State;

typedef struct stateinfo {
    int score;
    int highscore;
    int lives;
    int speed;
    int foodx;
    int foody;  
    int foodcounter;
    bool is_over;
    bool is_paused;
    Vector snake;
}* StateInfo;

State state_create(int lives, int highscore);

State state_update(State state);

void state_destroy(State state);

StateInfo state_info(State state);

void stateinfo_destroy(StateInfo info);

bool is_game_over(State state);


