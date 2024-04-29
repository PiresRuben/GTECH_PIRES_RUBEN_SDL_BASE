#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "draw_move.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SQUARE_SIZE 20
#define SPEED 0.1

void growSnake(Snake* snake) {
    if (snake->length == snake->capacity) {
        snake->capacity *= 2;
        snake->body = realloc(snake->body, sizeof(Square) * snake->capacity);
    }
    snake->body[snake->length] = snake->body[snake->length - 1];
    snake->length++;
}
