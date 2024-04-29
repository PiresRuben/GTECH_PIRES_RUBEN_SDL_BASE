#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "draw_move.h"
#include "mouvement.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SQUARE_SIZE 20
#define SPEED 0.1


// pour collision mais marche pas
//int checkSelfCollision(Snake* snake) {
//    for (int i = 1; i < snake->length; i++) {
//        if (snake->body[i].x == snake->body[0].x && snake->body[i].y == snake->body[0].y) {
//            return 1; // Collision detected
//        }
//    }
//    return 0; // No collision
//}

int main() {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "Snake");

    Snake snake;
    snake.body = malloc(sizeof(Square) * 10); // Initial capacity
    snake.length = 1;
    snake.capacity = 10;
    snake.body[0] = (Square){ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };

    Square food = { 0, 0 };
    srand(time(NULL));

    int quit = 0;
    Uint32 last_time = SDL_GetTicks();

    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case SDLK_UP:
                    moveSnake(&snake, 0, -SQUARE_SIZE);
                    break;
                case SDLK_DOWN:
                    moveSnake(&snake, 0, SQUARE_SIZE);
                    break;
                case SDLK_LEFT:
                    moveSnake(&snake, -SQUARE_SIZE, 0);
                    break;
                case SDLK_RIGHT:
                    moveSnake(&snake, SQUARE_SIZE, 0);
                    break;
                }
            }
        }

        Uint32 current_time = SDL_GetTicks();
        if (current_time > last_time + 5000) { // Change food color every 5 seconds
            food.x = rand() % (SCREEN_WIDTH / SQUARE_SIZE) * SQUARE_SIZE;
            food.y = rand() % (SCREEN_HEIGHT / SQUARE_SIZE) * SQUARE_SIZE;
            last_time = current_time;
        }

        // Check if snake eats food
        if (snake.body[0].x == food.x && snake.body[0].y == food.y) {
            growSnake(&snake);
            food.x = rand() % (SCREEN_WIDTH / SQUARE_SIZE) * SQUARE_SIZE;
            food.y = rand() % (SCREEN_HEIGHT / SQUARE_SIZE) * SQUARE_SIZE;
        }

        //// Check for self-collision, excluding the head if it's on the food
        //if (!(snake.body[0].x == food.x && snake.body[0].y == food.y) && checkSelfCollision(&snake)) {
        //    quit = 1; // End game if self-collision detected
        //}

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for (int i = 0; i < snake.length; i++) {
            if (i == 0) {
                drawSquare(renderer, snake.body[i].x, snake.body[i].y, 255, 255, 255);
            }
            else {
                drawSquare(renderer, snake.body[i].x, snake.body[i].y, 0, 255, 0); // Color for additional snake parts
            }
        }

        drawSquare(renderer, food.x, food.y, rand() % 256, rand() % 256, rand() % 256);

        SDL_RenderPresent(renderer);
        SDL_Delay(SPEED * 1000);
    }

    free(snake.body);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}