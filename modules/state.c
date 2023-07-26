#include "state.h"
#include <unistd.h>
#include <time.h>


struct state{
    bool is_paused;
    bool is_over;
    int score;
    int lives;
    time_t t;
    float speed;
    int foodx;
    int foody;
    int foodcounter;
    int highscore;
    Vector snake;
    Direction direction;
};

State state_create(int lives, int highscore){
    srand(SCALE);
    State state = malloc(sizeof(*state));
    state->direction = RIGHT;
    state->foodx = (rand()%(SCREEN_WIDTH/SCALE))*SCALE;
    state->foody = (rand()%(SCREEN_HEIGHT/SCALE))*SCALE;
    state->score = 0;
    state->lives = lives;
    state->speed = 1;
    state->t = 0;
    state->foodcounter = 1;
    state->is_over = false;
    state->highscore = highscore;
    state->is_paused = false;
    state->snake = vector_create(0, (DestroyFunc)destroy_snake_node);
    SnakeNode head = create_snake_node(SCREEN_WIDTH/(2*SCALE),SCREEN_HEIGHT/(2*SCALE));
    vector_insert_last(state->snake, head);
    vector_insert_last(state->snake, create_snake_node(SCREEN_WIDTH/(2*SCALE)-1,SCREEN_HEIGHT/(2*SCALE)));
    return state;
}

StateInfo state_info(State state){
    StateInfo info = malloc(sizeof(*info));
    info->score = state->score;
    info->lives = state->lives;
    info->snake = state->snake;
    info->foodx = state->foodx;
    info->foody = state->foody;
    info->is_over = state->is_over;
    info->highscore = state->highscore;
    info->is_paused = state->is_paused;
    info->foodcounter = state->foodcounter;
    return info;
}

bool is_game_over(State state){
    return state->is_over;
}

State state_update(State state){
    if(state->is_over){
        return state;
    }
    if(IsKeyPressed(KEY_P)){
        state->is_paused = !state->is_paused;
    }
    if(state->is_paused){
        return state;
    }
    if(state->t != 0 && difftime(time(NULL), state->t) > 3){
        state->foodx = (rand()%(SCREEN_WIDTH/SCALE))*SCALE;
        state->foody = (rand()%(SCREEN_HEIGHT/SCALE))*SCALE;
        state->t =0;
        state->foodcounter = 1;
    }
    SnakeNode head = (SnakeNode)vector_get_at(state->snake, 0);
    int x = get_x(head);
    int y = get_y(head);
    x = x < 0 ? SCREEN_WIDTH + x : x % SCREEN_WIDTH;
    y = y < 0 ? SCREEN_HEIGHT + y : y % SCREEN_HEIGHT;
    int CrashHeadX = x;
    int CrashheadY = y;
    if(state->foodcounter < 6){
        if(x == state->foodx && y == state->foody){
            state->score++;
            state->foodcounter++;
            state->foodx = (rand()%(SCREEN_WIDTH/SCALE))*SCALE;
            state->foody = (rand()%(SCREEN_HEIGHT/SCALE))*SCALE;
            SnakeNode node = create_snake_node(x, y);
            vector_insert_last(state->snake, node);
            if(state->foodcounter == 6 && state->t == 0){
                state->t = time(NULL);
            }
        }
    }
    else{
        if(CheckCollisionRecs((Rectangle){x, y, SCALE, SCALE}, (Rectangle){state->foodx, state->foody, SCALE*2, SCALE*2})){
            state->score += 5;
            state->foodcounter = 1;
            state->t = 0;
            state->foodx = (rand()%(SCREEN_WIDTH/SCALE - 1))*SCALE;
            state->foody = (rand()%(SCREEN_HEIGHT/SCALE - 1))*SCALE;
            SnakeNode node = create_snake_node(x, y);
            vector_insert_last(state->snake, node);
        }
    }
    if(state->direction == LEFT || state->direction == RIGHT){
        if(IsKeyPressed(KEY_UP)){
            state->direction = UP;
        }
        else if(IsKeyPressed(KEY_DOWN)){
            state->direction = DOWN;
        }
    }
    else if(state->direction == DOWN || state->direction == UP){
        if(IsKeyPressed(KEY_RIGHT)){
            state->direction = RIGHT;
        }
        else if(IsKeyPressed(KEY_LEFT)){
            state->direction = LEFT;
        }
    }
    switch(state->direction){
        case RIGHT:
            set_x(head, x + state->speed*SCALE);
            break;
        case DOWN:
            set_y(head, y + state->speed*SCALE);
            break;
        case LEFT:
            set_x(head, x - state->speed*SCALE);
            break;
        case UP:
            set_y(head, y - state->speed*SCALE);
            break;
    }
    for(int i = 1; i < vector_size(state->snake); i++){
        SnakeNode node = (SnakeNode)vector_get_at(state->snake, i);
        int xnode = get_x(node);
        int ynode = get_y(node);
        if(xnode == CrashHeadX && ynode == CrashheadY){
            int lives = --state->lives;
            if(state->score > state->highscore){
                state->highscore = state->score;
            }
            if(lives == 0){
                state->is_over = true;
                return state;
            }
            state_destroy(state);
            state = state_create(lives, state->highscore);
            sleep(1);
            return state;
        }
        set_x(node, x);
        set_y(node, y);
        x = xnode;
        y = ynode;
        head = node;    
    }
    return state;
}

void stateinfo_destroy(StateInfo info){
    free(info);
}

void state_destroy(State state){
    vector_destroy(state->snake);
    free(state);
}