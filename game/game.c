#include "raylib.h"
#include "interface.h"

State state;

int main(){

    state = state_create(3);
    interface_init();

    while(!WindowShouldClose()){
        if((IsKeyDown(KEY_RIGHT_SHIFT) || IsKeyDown(KEY_LEFT_SHIFT)) && IsKeyPressed(KEY_R)){
            state_destroy(state);
            state = state_create(3);
        }
        if(state!=NULL)
            state = state_update(state);
        interface_draw(state);
        if(state == NULL){
            if(IsKeyPressed(KEY_R)){
                state = state_create(3);
            }
        }
    }

    interface_close();
}