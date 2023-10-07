#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int height = 20, width = 20, score, fruitx, fruity, x, y, gamestate, direction,
    MOVEMENT_SPEED;

void fruit() {
  fruitx = rand() % width;
  fruity = rand() % height;
  while (fruitx == 0 || fruity == 0) {
    fruitx = rand() % width;
    fruity = rand() % height;
  }
}
void setup() {
  x = width / 2;
  y = height / 2;
  direction = KEY_UP;
  MOVEMENT_SPEED = 150000;
  initscr();
  raw();
  keypad(stdscr, TRUE);
  refresh();
  nodelay(stdscr, TRUE);
  fruit();
}
void draw() {
  int i;
  int j;
  clear();
  for (i = 0; i <= height; i++) {
    for (j = 0; j <= width; j++) {
      if (j == x && i == y) {
        printw("@");
      } else if (j == fruitx && i == fruity) {
        printw("&");
      } else {
        if (i == 0 || i == height) {
          printw("*");
        } else if (j == 0 || j == width) {
          printw("*");
        } else {
          printw(" ");
        }
      }
    }
    printw("\n");
  }
}

void game() {
  if (x == 0 || x == width) {
    gamestate = 1;
  } else if (x == width || x == 0 || y == height || y == 0) {

    gamestate = 1;
  }
  if (x == fruitx && y == fruity) {
    score++;
    fruit();
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
  while (!gamestate) {
    draw();
    int ch = getch();
    input(direction);
    game();
    if (ch != ERR) {
      direction = ch;
    }
    usleep(MOVEMENT_SPEED);
  }
  return 0;
}
