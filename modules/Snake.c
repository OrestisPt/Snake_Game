#include "Snake.h"

struct snake_node{
    int x;
    int y;
};

SnakeNode create_snake_node(int x, int y){
    SnakeNode node = malloc(sizeof(*node));
    node->x = x*10;
    node->y = y*10;
    return node;
}

int get_x(SnakeNode node){
    return node->x;
}

int get_y(SnakeNode node){
    return node->y;
}

void set_x(SnakeNode node, int x){
    node->x = x;
}

void set_y(SnakeNode node, int y){
    node->y = y;
}

void destroy_snake_node(SnakeNode node){
    free(node);
}