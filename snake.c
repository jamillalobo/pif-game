#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LIVES 10
#define MIN_LIVES 0

typedef struct {
    int x, y;
} Position;

// Declaração antecipada da função spawn_object
void spawn_object(Position *pos, int max_x, int max_y);

// Inicializa o jogo e a interface
void init_game(Position *snake, Position *fruit, Position *hole, int *lives) {
    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    timeout(100);
    
    *lives = 5;
    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);
    snake->x = max_x / 2;
    snake->y = max_y / 2;
    spawn_object(fruit, max_x, max_y);
    spawn_object(hole, max_x, max_y);
}

// Gera a posição de um objeto (fruta ou buraco) aleatoriamente
void spawn_object(Position *pos, int max_x, int max_y) {
    pos->x = rand() % max_x;
    pos->y = rand() % max_y;
}

// Atualiza a posição da cobra com base na entrada do usuário
void update_snake_position(Position *snake, int ch) {
    switch(ch) {
        case KEY_UP: snake->y--; break;
        case KEY_DOWN: snake->y++; break;
        case KEY_LEFT: snake->x--; break;
        case KEY_RIGHT: snake->x++; break;
    }
}
// Verifica colisões e atualiza o estado do jogo
void check_collisions(Position *snake, Position *fruit, Position *hole, int *lives) {
    if (snake->x == fruit->x && snake->y == fruit->y) {
        (*lives)++;
        if (*lives > MAX_LIVES) *lives = MAX_LIVES;
        spawn_object(fruit, COLS, LINES);
    } else if (snake->x == hole->x && snake->y == hole->y) {
        (*lives)--;
        if (*lives < MIN_LIVES) *lives = MIN_LIVES;
        attron(COLOR_PAIR(rand() % 7 + 1));  // Muda a cor para indicar o efeito do buraco
        spawn_object(hole, COLS, LINES);
    }
}

// Exibe a interface do jogo
void draw_game(Position *snake, Position *fruit, Position *hole, int lives) {
    clear();
    mvprintw(snake->y, snake->x, "@");
    mvprintw(fruit->y, fruit->x, "*");
    mvprintw(hole->y, hole->x, "*");
    mvprintw(0, 0, "Vidas: %d", lives);
    refresh();
}

// Finaliza o jogo
void end_game() {
    timeout(-1);
    getch();
    endwin();
}

int main() {
    srand(time(0));
    Position snake, fruit, hole;
    int lives;
    
    init_game(&snake, &fruit, &hole, &lives);
    
    while (lives > 0 && lives < MAX_LIVES) {
        int ch = getch();
        update_snake_position(&snake, ch);
        check_collisions(&snake, &fruit, &hole, &lives);
        draw_game(&snake, &fruit, &hole, lives);
    }
    
    end_game();
    if (lives <= 0) printf("Game Over!\n");
    else printf("Victory!\n");
    
    return 0;
}

// ### How to compile & run

// ```
// gcc -I/usr/include/ -osnake snake.c -lncurses
// ./snake
// ```

// ### Dependencies

// snake.c relies on ncurses to draw to the terminal. To install on Ubuntu/Debian, use:

// ```
// sudo apt-get install lib32ncurses5-dev
// ```
