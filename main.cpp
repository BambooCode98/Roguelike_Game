#include <string>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <ncurses.h>
#include "player.h"


using namespace std;


int main() {


  initscr();

  cbreak();
  noecho();
  clear();

  
  WINDOW *display = newwin(10, 50, 0, 0);
  box(display, 0, 0);
  refresh();


  int maxX, maxY;
  getmaxyx(display,maxY,maxX);

  keypad(display, true);

  Player player(1,1,'@',display);

  player.setMaxWindowSize(maxX, maxY);

  while(true) {
    player.getmv();
    player.displayToken();
    wrefresh(display);
  }

  delwin(display);
  endwin();

  return 0;
}

