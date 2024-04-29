#ifndef DRAW_MOVE_H
#define DRAW_MOVE_H

#include <SDL.h>

typedef struct {
    int x;
    int y;
} Square;

typedef struct {
    Square* body;
    int length;
    int capacity;
} Snake;

void drawSquare(SDL_Renderer* renderer, int x, int y, int r, int g, int b);

void moveSnake(Snake* snake, int dx, int dy);
#endif