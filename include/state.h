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
    int lives;
    int speed;
    int foodx;
    int foody;  
    bool is_paused;
    Vector snake;
}* StateInfo;

State state_create(int lives);

State state_update(State state);

void state_destroy(State state);

StateInfo state_info(State state);

void stateinfo_destroy(StateInfo info);


