#include "raylib.h"
#include "interface.h"

State state;

int main(){

    state = state_create(3, 0);
    interface_init();

    while(!WindowShouldClose()){
        if((IsKeyDown(KEY_RIGHT_SHIFT) || IsKeyDown(KEY_LEFT_SHIFT)) && IsKeyPressed(KEY_R)){
            state_destroy(state);
            state = state_create(3, 0);
        }
        state = state_update(state);
        interface_draw(state);
        if(is_game_over(state)){
            if(IsKeyPressed(KEY_R)){
                state_destroy(state);
                state = state_create(3, 0);
            }
        }
    }
    state_destroy(state);
    interface_close();
}