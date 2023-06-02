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
  _HUDWIN = newwin(LINES/5,COLS/3,0,COLS/1.5);
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
  //  mvwprintw(_MenuWIN,items.size()+1,2,"             ");
  // for(string i: items) {
  //   // _menuItemsY+=1;
  //   // if(items.size() > 0) mvwprintw(_MenuWIN,items.size()-1,2,"             ");
  //   mvwprintw(_MenuWIN,items.begin()+1,2,"%i. %s", items.size(),i.c_str());
  //   // mvwprintw(_MenuWIN,items.size()-1,2,"             ");
  //   // refresh();
  // }
  for(int i=0; i<items.size();i++) {
    mvwprintw(_MenuWIN,i+1,2,"%i. %s  ", i+1,items[i].c_str());
  }
  // wmove(_MenuWIN,1,1);
  // wclrtobot(_MenuWIN);
  wclrtobot(_MenuWIN);
  box(_MenuWIN,0,0);
  mvwprintw(_MenuWIN,0,0,"Inventory");
  wrefresh(_MenuWIN);
}

void Game::updateStatusBar(int life, float exp, int att) {
  playerHealthBar(life);
  playerExp(exp);
  playerAttackStat(att);
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

void Game::playerHealthBar(int life = 20) {
  wrefresh(_HUDWIN);
  mvwprintw(_HUDWIN,1,2,"HP: %i/%i   ",life, 20);
}

void Game::playerExp(float exp) {
  wrefresh(_HUDWIN);
  mvwprintw(_HUDWIN,2,2,"EXP: %.1f/%i",exp, 20);
}

void Game::playerAttackStat(int att) {
  wrefresh(_HUDWIN);
  mvwprintw(_HUDWIN,3,2,"Attack: %i",att);
}



bool Game::gameOver(int life) {
  if(life == 0) {
    _gameOver = true;
  }

  return _gameOver;
}