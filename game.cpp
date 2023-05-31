#include <string>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <ncurses.h>
#include "game.h"

using namespace std;



Game::Game() {

}



void Game::createHUD() {
  _HUDWIN = newwin(LINES/8,COLS/3,0,COLS/1.5);
  wrefresh(_HUDWIN);
  box(_HUDWIN,0,0);
  wprintw(_HUDWIN,"Status");
}


void Game::createInventory() {
  _MenuWIN = newwin(LINES/2,COLS/3,5,COLS/1.5);
  wrefresh(_MenuWIN);
  box(_MenuWIN,0,0);
  wprintw(_MenuWIN,"Inventory");
}

void Game::updateInventoryWindow(vector<string> items) {
  //  mvwprintw(_MenuWIN,1,5,"items length: %d", items.size());
  for(string i: items) {
    // _menuItemsY+=0.5;
    mvwprintw(_MenuWIN,items.size(),2,"%s", i.c_str());
  }
  // wmove(_MenuWIN,1,1);
  wclrtobot(_MenuWIN);
  box(_MenuWIN,0,0);
  mvwprintw(_MenuWIN,0,0,"Inventory");
  wrefresh(_MenuWIN);
}

void Game::updateStatusBar(int life) {
  PlayerHealthBar(life);
}


void Game::getMaxWindowSize(int xmax, int ymax) {

  //get window size for outer bounds detection
  _xMax = xmax;
  _yMax = ymax;
}

void Game::delHUDWindow() {
  wrefresh(_HUDWIN);
  delwin(_HUDWIN);
}

void Game::delMenuWindow() {
  wrefresh(_MenuWIN);
  delwin(_MenuWIN);
}

void Game::PlayerHealthBar(int life = 20) {
  wrefresh(_HUDWIN);
  mvwprintw(_HUDWIN,1,2,"HP: %i/%i",life, 20);
}