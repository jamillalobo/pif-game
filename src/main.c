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
    
    // Apaga a nave na posição antiga
    screenGotoxy(x, y);         printf("     ");
    screenGotoxy(x - 1, y + 1); printf("      ");
    screenGotoxy(x - 2, y + 2); printf("      ");
    
    // Atualiza a posição da nave
    x = nextX;
    y = nextY;

    // Desenha a nave na nova posição
    screenGotoxy(x, y);         printf("  ^  ");  // Ponta da nave
    screenGotoxy(x - 1, y + 1); printf(" / \\ "); // Asas da nave
    screenGotoxy(x - 2, y + 2); printf("/   \\"); // Base da nave
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

    // Inicializa as bibliotecas
    screenInit(1);
    keyboardInit();
    timerInit(50);

    desenhaNave(x, y); // Desenha a nave na posição inicial
    screenUpdate();

    while (ch != 10) { // Sai do loop quando a tecla Enter (código 10) é pressionada
        // Lida com a entrada do usuário
        if (keyhit()) {
            ch = readch();
            printKey(ch);
            screenUpdate();
        }

        if (timerTimeOver() == 1) {
            int newX = x + incX;
            int newY = y + incY;

            // Inverte a direção caso atinja as bordas da tela
            if (newX >= (MAXX - 5) || newX <= MINX + 1) incX = -incX;
            if (newY >= MAXY - 3 || newY <= MINY + 1) incY = -incY;

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