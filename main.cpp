#include <string>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>
#include <ncurses.h>
#include "player.h"
#include "game.h"
#include "enemy.h"


using namespace std;


int main() {
  bool end = false;



  initscr();

  cbreak();
  noecho();
  clear();
  curs_set(0);

  
  WINDOW *display = newwin(LINES, COLS, 0, 0);
  box(display, 0, 0);
  wborder(display,' ',' ',' ',' ',' ',' ',' ',' ');
  
  refresh();

  string level_ascii;
  int num_of_rows, num_of_cols;

  ifstream levelFiles("levels/level1.txt");
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
  // Enemy monster(3,9,'M',display,10,5);
  Game game;
    // wrefresh(display);

  player.getMaxWindowSize(maxX, maxY);
  game.createHUD();
  game.createInventory();

    // refresh();
  while(!end) {
    player.getmv();
    game.updateInventoryWindow(player.updatePlayerInventory());
    // refresh();
    game.updateStatusBar(player.getHealth(), player.getExp(), player.getAttack());
    player.displayToken();
    // monster.displayToken();
    // wrefresh(display);
  // mvwprintw(display,LINES/2,COLS/2,"Lines: %d, Cols: %d", LINES,COLS);
    end = game.gameOver(player.getHealth());

  }

  game.delHUDWindow();
  game.delMenuWindow();
  delwin(display);
  endwin();

  return 0;
}

