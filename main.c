#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define HEIGHT 20
#define WIDTH 20

struct position {
  int x;
  int y;
};

struct position tail[HEIGHT * WIDTH];

int x, y, gamestate, score, fruitx, fruity, direction, taillong;

void fruit() {
  fruitx = rand() % WIDTH;
  fruity = rand() % HEIGHT;
  while (fruitx == 0 || fruity == 0) {
    fruitx = rand() % WIDTH;
    fruity = rand() % HEIGHT;
  }
}

void setup() {
  srand(time(NULL));
  initscr();
  raw();
  keypad(stdscr, TRUE);
  refresh();
  nodelay(stdscr, TRUE);
  fruit();
  direction = KEY_UP;
  int i;
  for (i = 0; i < WIDTH * HEIGHT; i++) {
    tail[i].x = -1;
    tail[i].y = -1;
  }
  score = 6;
  x = WIDTH / 2;
  y = HEIGHT / 2;
}

void draw() {
  erase(); // Clear the screen
  for (int k = 0; k < taillong; k++) {
    mvprintw(tail[k].y, tail[k].x, "@");
  }

  mvprintw(y, x, "@");

  mvprintw(fruity, fruitx, "&");

  for (int i = 0; i < HEIGHT + 1; i++) {
    for (int j = 0; j < WIDTH + 1; j++) {
      if (i == 0 || i == HEIGHT || j == 0 || j == WIDTH) {
        mvprintw(i, j, "#");
      }
    }
  }

  mvprintw(HEIGHT + 1, 0, "score: %d", score);

  refresh();
}

void game() {
  if (x == fruitx && y == fruity) {
    fruit();
    score++;
    taillong++;
  }
  for (int j = 1; j < taillong; j++) {
    if (tail[j].x == x && tail[j].y == y) {
      gamestate = 1;
    }
  }

  for (int i = taillong - 1; i > 0; i--) {
    tail[i] = tail[i - 1];
  }
  tail[0].x = x;
  tail[0].y = y;

  if (x == 0 || x == WIDTH || y == 0 || y == HEIGHT) {
    gamestate = 1;
  }
}
void input(int direction) {
  switch (direction) {
  case KEY_UP:
    y--;
    break;
  case KEY_DOWN:
    y++;
    break;
  case KEY_LEFT:
    x--;
    break;
  case KEY_RIGHT:
    x++;
    break;
  }
}

int main(void) {
  setup();

  int ch;
  while (!gamestate) {
    ch = getch();
    if (ch != ERR) {

      direction = ch;
    }
    input(direction);

    draw();
    game();
    usleep(100000);
  }
  if (gamestate) {
    mvprintw(HEIGHT + 6, 0, "Press enter to exit");
    refresh();

    while ((ch = getch()) != '\n' && ch != '\r')
      ;
  }
  endwin();
  return 0;
}
