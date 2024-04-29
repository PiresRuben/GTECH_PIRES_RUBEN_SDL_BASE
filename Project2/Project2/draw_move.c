#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SQUARE_SIZE 20
#define SPEED 0.1

typedef struct {
    int x;
    int y;
} Square;

typedef struct {
    Square* body;
    int length;
    int capacity;
} Snake;

void drawSquare(SDL_Renderer* renderer, int x, int y, int r, int g, int b) {
    SDL_Rect rect = { x, y, SQUARE_SIZE, SQUARE_SIZE };
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void moveSnake(Snake* snake, int dx, int dy) {
    for (int i = snake->length - 1; i > 0; i--) {
        snake->body[i] = snake->body[i - 1];
    }
    snake->body[0].x += dx;
    snake->body[0].y += dy;
}