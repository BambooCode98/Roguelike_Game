#include <string>
#include <cstdlib>
// #include <cstdio>
#include <iostream>
#include <fstream>
#include <ncurses.h>
#include "player.h"


using namespace std;


int main() {




  initscr();

  cbreak();
  noecho();
  clear();
  curs_set(0);

  
  WINDOW *display = newwin(LINES, COLS, 0, 0);
  box(display, 0, 0);
  refresh();

  string level_ascii;
  int num_of_rows, num_of_cols;

  ifstream levelFiles("levels/level2.txt");
  if(levelFiles.is_open()) {

    while(getline(levelFiles,level_ascii)) {
      // if(level_ascii == "#") num_of_cols++;
      wprintw(display,level_ascii.c_str());
      wprintw(display,"\n");

    }
    levelFiles.close();
  }

  int maxX, maxY;
  getmaxyx(display,maxY,maxX);

  keypad(display, true);

  Player player(1,1,'@',display);

  player.getMaxWindowSize(maxX, maxY);

  while(true) {
    player.getmv();
    player.displayToken();
    wrefresh(display);
  }

  delwin(display);
  endwin();

  return 0;
}

