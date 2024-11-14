#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

#define MAX_LIVES 10
#define MIN_LIVES 0
#define MAX_OBJECTS 100  

typedef struct {
    int x, y;
} Position;

Position all_objects[MAX_OBJECTS]; 

int xMan = MAXX / 2, yMan = MAXY / 2; 
int incX = 1, incY = 0;

int collision_count = 0;
int object_count = 0;

void spawn_object(Position *pos, int max_x, int max_y);

void init_game(Position *food, Position *hole, int *lives) {
    screenInit(1);
    keyboardInit();
    timerInit(100);

    *lives = 5;

    int max_x = MAXX;
    int max_y = MAXY;

    getmaxyx(stdscr, max_x, max_y);
    spawn_object(food, max_x, max_y);
    spawn_object(hole, max_x, max_y);
}

void add_object(Position *pos) {
    if (object_count < MAX_OBJECTS) {
        all_objects[object_count++] = *pos;
    }
}

void spawn_object(Position *pos, int max_x, int max_y) {
    pos->x = rand() % (max_x - 5) + 2;
    pos->y = rand() % (max_y - 5) + 2;
    add_object(pos);

    screenSetColor(RED, DARKGRAY);
    screenGotoxy(pos->x, pos->y);
    printf("o");
}

void delete_object(Position *pos) {
    screenGotoxy(pos->x, pos->y);
    printf(" ");
}

void clear_all_objects() {
    for (int i = 0; i < object_count; i++) {
        delete_object(&all_objects[i]);
    }
    object_count = 0; 
}

void drawMan(int nextX, int nextY) {
    screenSetColor(CYAN, DARKGRAY);
    
    screenGotoxy(xMan, yMan);         
    printf(" ");

    xMan = nextX;
    yMan = nextY;

    screenGotoxy(xMan, yMan);         
    printf("@");
}

void initialize_random() {
    srand(time(NULL));
}

int getRandomColor() {
    return (rand() % 8);  
}

void setGameAreaBackground(int color) {
    for (int y = MINY + 2; y <= MAXY; y++) {  
        for (int x = MINX + 2; x < MAXX; x++) {
            printf("\033[%d;%dH", y, x); 
            printf("\033[48;5;%dm ", color); 
        }
    }
    printf("\033[H"); 
}

void check_borders(int *lives) {
    if (xMan <= MINX || xMan >= MAXX || yMan <= MINY || yMan >= MAXY) {
        (*lives)--;
        collision_count++;

        if (*lives < MIN_LIVES) {
            *lives = MIN_LIVES;
        }
    }
}

void check_collisions(Position *food, Position *hole, int *lives) {
    if (xMan == food->x && yMan == food->y) {
        (*lives)++;
        collision_count++;
        if (*lives > MAX_LIVES) *lives = MAX_LIVES;

        clear_all_objects();  
        spawn_object(food, MAXX, MAXY);
        spawn_object(hole, MAXX, MAXY);

    } else if (xMan == hole->x && yMan == hole->y) {
        (*lives)--;
        collision_count++;
        if (*lives < MIN_LIVES) *lives = MIN_LIVES;

        int randomBgColor = getRandomColor() + 40;  
        setGameAreaBackground(randomBgColor);

        clear_all_objects(); 
        spawn_object(hole, MAXX, MAXY);
        spawn_object(food, MAXX, MAXY);
    }
}

void draw_lives(int lives) {
    screenSetColor(WHITE, DARKGRAY);
    screenGotoxy(1, MAXY);
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

    Position food, hole;
    init_game(&food, &hole, &lives);
    drawMan(xMan, yMan);
    screenUpdate();

    int spawn_counter = 0;

    while (lives > 0 && lives < MAX_LIVES && ch != 10) {
        if (timerTimeOver() == 1) {
            int newX = xMan + incX;
            int newY = yMan + incY;

            if (newX >= (MAXX - 2) || newX <= MINX + 1) {
                incX = -incX;
                check_borders(&lives);
            }
            if (newY >= (MAXY - 1) || newY <= (MINY + 1)) {
                incY = -incY;
                check_borders(&lives);
            }

            drawMan(newX, newY);
        }

        if (keyhit()) {
            ch = readch();
            switch (ch) {
                case 'A': // seta pra cima
                    incX = 0;
                    incY = -1;
                    break;
                case 'B': // seta pra baixo
                    incX = 0;
                    incY = 1;
                    break;
                case 'D': // seta pra esquerda
                    incX = -1;
                    incY = 0;
                    break;
                case 'C': // seta pra direita
                    incX = 1;
                    incY = 0;
                    break;
                case 'q':
                    lives = 0;
                    break;
            }
        }
        check_collisions(&food, &hole, &lives);
        draw_lives(lives);
        screenUpdate();
    }

    spawn_counter++;

    if (spawn_counter >= 35) {
        spawn_object(&hole, MAXX, MAXY);
        spawn_object(&food, MAXX, MAXY);
        spawn_counter = 0;
    }
    
    end_game();
    printf("Total de colisões: %d\n", collision_count);

    if (lives <= 0) printf("Game Over!\n");
    else printf("Victory!\n");

    return 0;
}
