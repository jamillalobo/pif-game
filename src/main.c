/**
 * main.h
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
*/

#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

int x = MAXX/2, y = MAXY/2; // Posição inicial da nave
int incX = 1, incY = 0; // Incrementos para movimentação da nave

void desenhaCobra(int nextX, int nextY) {
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

void spawn_object() {
    int objX = rand() % (MAXX - 5) + 1; // Garante que o objeto esteja dentro dos limites
    int objY = rand() % (MAXY - 5) + 1;

    screenSetColor(RED, DARKGRAY);
    screenGotoxy(objX, objY);
    printf("*"); 
}

int main() {
    static int ch = 0;
    srand(time(0));

    screenInit(1);
    keyboardInit();
    timerInit(100);

    desenhaCobra(x, y);
    screenUpdate();

    int spawn_counter = 0;

    while (ch != 10) {
        if (keyhit()) {
            ch = readch();
            if (ch == 'd') {
                incX = 1;
                incY = 0;
            } else if (ch == 'a') {
                incX = -1;
                incY = 0;
            } else if (ch == 's') {
                incX = 0;
                incY = 1;
            } else if (ch == 'w') {
                incX = 0;
                incY = -1;
            }
            printKey(ch);
            screenUpdate();
        }

        if (timerTimeOver() == 1) {
            int newX = x + incX;
            int newY = y + incY;

            if (newX >= (MAXX - 2) || newX <= MINX + 1){
                incX = -incX;
            }
            if (newY >= (MAXY - 1) || newY <= (MINY + 1)){
                incY = -incY;
            }

            desenhaCobra(newX, newY);
            screenUpdate();

            spawn_counter++;

            if (spawn_counter >= 35) {
                spawn_object();
                spawn_counter = 0; // Reseta o contador
            }
        }
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}