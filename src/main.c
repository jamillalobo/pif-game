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
#include <ncurses.h>

// pontuação limite de vidas
#define MAX_LIVES 10
#define MIN_LIVES 0

struct {
    int x, y;
} typedef Position;

int xSnake = MAXX/2, ySnake = MAXY/2; 
int incX = 1, incY = 0; // Incrementos para movimentação da cobra

// Variável para armazenar a contagem de colisões
int collision_count = 0;

// Declaração antecipada da função spawn_object
void spawn_object(Position *pos, int max_x, int max_y);

void init_game(Position *fruit, Position *hole, int *lives) {
    screenInit(1);
    keyboardInit();
    timerInit(100);

    *lives = 5;

    int max_x = MAXX;
    int max_y = MAXY;

    getmaxyx(stdscr, max_x, max_y);
    spawn_object(fruit, max_x, max_y);
    spawn_object(hole, max_x, max_y);
}

void spawn_object(Position *pos, int max_x, int max_y) {
    pos->x = rand() % (MAXX - 5) + 1;
    pos->y = rand() % (MAXY - 5) + 1;

    screenSetColor(RED, DARKGRAY);
    screenGotoxy(pos->x, pos->y);
    printf("o");
}

void desenhaCobra(int nextX, int nextY) {
    screenSetColor(CYAN, DARKGRAY);
    
    screenGotoxy(xSnake, ySnake);         
    printf(" ");

    xSnake = nextX;
    ySnake = nextY;

    screenGotoxy(xSnake, ySnake);         
    printf("@");
}

void check_collisions(Position *fruit, Position *hole, int *lives) {
    if (xSnake == fruit->x && ySnake == fruit->y) {
        (*lives)++;
        collision_count++; // Incrementa a contagem de colisões com a fruta
        if (*lives > MAX_LIVES) *lives = MAX_LIVES;
        spawn_object(fruit, MAXX, MAXY);
    } else if (xSnake == hole->x && ySnake == hole->y) {
        (*lives)--;
        collision_count++; // Incrementa a contagem de colisões com o buraco
        if (*lives < MIN_LIVES) *lives = MIN_LIVES;
        attron(COLOR_PAIR(rand() % 7 + 1));  // Muda a cor para indicar o efeito do buraco
        spawn_object(hole, MAXX, MAXY);
    }
}

void draw_lives(int lives) {
    screenSetColor(WHITE, BLACK);
    screenGotoxy(0, 0);
    printf("Vidas: %d", lives);
}

void end_game() {
    keyboardDestroy();
    screenDestroy();
    timerDestroy();
}

int main() {
    static int ch = 0;
    srand(time(0));
    int lives;

    Position fruit, hole;
    init_game(&fruit, &hole, &lives);
    desenhaCobra(xSnake, ySnake);
    screenUpdate();

    int spawn_counter = 0;

    while (lives > 0 && lives < MAX_LIVES) {
        if (timerTimeOver() == 1) {
            int newX = xSnake + incX;
            int newY = ySnake + incY;

            // Verifique as bordas para a colisão e rebote
            if (newX >= (MAXX - 2) || newX <= MINX + 1) {
                incX = -incX;
            }
            if (newY >= (MAXY - 1) || newY <= (MINY + 1)) {
                incY = -incY;
            }

            // Atualize a posição da cobra
            desenhaCobra(newX, newY);
        }

        // Verifique se há uma tecla pressionada
        if (keyhit()) {
            ch = readch();
            
            // Debug: Imprime o código da tecla pressionada
            printf("Tecla pressionada: %d\n", ch);

            switch (ch) {
                case 'A':
                    incX = 0;
                    incY = -1;
                    break;
                case 'B':
                    incX = 0;
                    incY = 1;
                    break;
                case 'D':
                    incX = -1;
                    incY = 0;
                    break;
                case 'C':
                    incX = 1;
                    incY = 0;
                    break;
                case 'q':
                    lives = 0;
                    break;
            }
        }

        check_collisions(&fruit, &hole, &lives);
        draw_lives(lives);
        screenUpdate();
    }

    spawn_counter++;

    if (spawn_counter >= 35) {
        spawn_object(&hole, MAXX, MAXY);
        spawn_object(&fruit, MAXX, MAXY);
        spawn_counter = 0; // Reseta o contador
    }
    

    end_game();
    
    // Exibe o total de colisões ao final do jogo
    printf("Total de colisões: %d\n", collision_count);

    if (lives <= 0) printf("Game Over!\n");
    else printf("Victory!\n");

    return 0;
}
