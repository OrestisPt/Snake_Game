#pragma once

#include <stdbool.h>
#include <stdlib.h>

typedef enum direction{
    UP,
    DOWN,
    LEFT,
    RIGHT
}Direction;

typedef struct snake_node *SnakeNode;

SnakeNode create_snake_node(int x, int y);

int get_x(SnakeNode node);

int get_y(SnakeNode node);

void set_x(SnakeNode node, int x);

void set_y(SnakeNode node, int y);

void destroy_snake_node(SnakeNode node);