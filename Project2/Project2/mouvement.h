#ifndef MOUVEMENT_H
#define MOUVEMENT_H

#include <SDL.h>
#include "draw_move.h"

//typedef struct {
//    int x;
//    int y;
//} Square;
//
//typedef struct {
//    Square* body;
//    int length;
//    int capacity;
//} Snake;

void growSnake(Snake* snake);

#endif
