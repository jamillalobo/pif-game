/**
 * main.h
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
*/

#include <string.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

int x = 34, y = 12; // Posição inicial da nave
int incX = 1, incY = 1; // Incrementos para movimentação da nave

void desenhaNave(int nextX, int nextY) {
    screenSetColor(CYAN, DARKGRAY);
    
    screenGotoxy(x, y);         
    printf(" ");

    x = nextX;
    y = nextY;

    screenGotoxy(x, y);         
    printf("O");
}

void printKey(int ch) {
    screenSetColor(YELLOW, DARKGRAY);
    screenGotoxy(35, 22);
    printf("Key code :");

    screenGotoxy(34, 23);
    printf("            ");
    
    if (ch == 27) 
        screenGotoxy(36, 23);
    else 
        screenGotoxy(39, 23);

    printf("%d ", ch);
    while (keyhit()) {
        printf("%d ", readch());
    }
}

int main() {
    static int ch = 0;

    screenInit(1);
    keyboardInit();
    timerInit(1000);

    desenhaNave(x, y);
    screenUpdate();

    while (ch != 10) { // Sai do loop quando a tecla Enter (código 10) é pressionada
        // Lida com a entrada do usuário
        if (keyhit()) {
            ch = readch();
            if (ch == 'd'){
                desenhaNave(x + 2, y);
            } else if (ch == 'a'){
                desenhaNave(x - 2, y);
            } else if (ch == 's'){
                desenhaNave(x, y + 2);
            } else if (ch == 'w'){
                desenhaNave(x, y - 2);
            }
            printKey(ch);
            screenUpdate();
        }

        if (timerTimeOver() == 1) {
            int newX = x + incX;
            int newY = y + incY;

            if (newX >= (MAXX - 1) || newX <= MINX + 1) incX = -incX;
            if (newY >= MAXY - 1 || newY <= MINY + 1) incY = -incY;

            desenhaNave(newX, newY);
            screenUpdate();
        }
    }

    // Finaliza as bibliotecas
    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}



// #include <SDL2/SDL.h>
// #include <stdio.h>

// int main(int argc, char *argv[]) {
//     // Initialize SDL
//     if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//         printf("Error initializing SDL: %s\n", SDL_GetError());
//         return -1;
//     }

//     // Create a window
//     SDL_Window *window = SDL_CreateWindow(
//         "Simple Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN
//     );
//     if (!window) {
//         printf("Error creating window: %s\n", SDL_GetError());
//         return -1;
//     }

//     // Create a renderer
//     SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//     if (!renderer) {
//         printf("Error creating renderer: %s\n", SDL_GetError());
//         SDL_DestroyWindow(window);
//         return -1;
//     }

//     // Game loop
//     int running = 1;
//     SDL_Event event;

//     while (running) {
//         // Handle events
//         while (SDL_PollEvent(&event)) {
//             if (event.type == SDL_QUIT) {
//                 running = 0;
//             }
//         }

//         // Clear the screen with a color
//         SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//         SDL_RenderClear(renderer);

//         // Present the screen
//         SDL_RenderPresent(renderer);

//         // Delay to control frame rate
//         SDL_Delay(16); // Roughly 60 FPS
//     }

//     // Cleanup
//     SDL_DestroyRenderer(renderer);
//     SDL_DestroyWindow(window);
//     SDL_Quit();

//     return 0;
// }