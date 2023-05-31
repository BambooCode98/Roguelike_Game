#include <string>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <ncurses.h>
#include "enemy.h"


using namespace std;


Enemy::Enemy(int y, int x, char playerToken, WINDOW *window) {
  _x = x;
  _y = y;
  _playerToken = playerToken;
  _curwin = window;
  _xMove = _yMove = 0;
}

void Enemy::getMaxWindowSize(int xmax, int ymax) {

  //get window size for outer bounds detection
  _xMax = xmax;
  _yMax = ymax;
}

void Enemy::mvPlayerUp() {
  mvwaddch(_curwin,_y,_x,'.');
  _y--;
  // _y_coord--;
  checkForWalls("up");
  checkForObjects();


  //prevent going offscreen
  if(_y <= 1) _y = 1;
}

void Enemy::mvPlayerDown() {
  mvwaddch(_curwin,_y,_x,'.');
  _y++;
  checkForWalls("down");
  checkForObjects();

  //prevent going offscreen
  if(_y >= _yMax-2) _y = _yMax-2;
}

void Enemy::mvPlayerLeft() {
  mvwaddch(_curwin,_y,_x,'.');
  _x--;
  // _x_coord--;
  checkForWalls("left");
  checkForObjects();


  //prevent going offscreen
  if(_x <= 1) _x = 1;
}

void Enemy::mvPlayerRight() {
  mvwaddch(_curwin,_y,_x,'.');
  _x++;
  // _x_coord++;
  checkForWalls("right");
  checkForObjects();


  //prevent going offscreen
  if(_x >= _xMax-2) _x = _xMax-2;
}

void Enemy::getCoordinates() {
  getyx(_curwin, _y_coord, _x_coord);
}

void Enemy::checkForObjects() {
  int object = mvwinch(_curwin,_y,_x);
  switch(object) {
    case int('@'):
      mvwprintw(_curwin,_yMax-5,5,"Hit by enemy.");
      wrefresh(_curwin);
      break;
  }
}

void Enemy::checkForWalls(string dir) {
  // getCoordinates();
  int wall = mvwinch(_curwin,_y,_x) & A_CHARTEXT;
  // wprintw(_curwin,"%d", wall);
  // mvwprintw(_curwin,_yMax/1.3,_xMax/1.5, "_y: %d _x: %d", _y, _x);

  if(dir == "down" && wall == '#') {
    _y--;
    _y_coord--;
  } else if(dir == "up" && wall == '#') {
    _y++;
    _y_coord++;
  } else if(dir == "right" && wall == '#') {
    _x--;
    _x_coord--;
  } else if(dir == "left" && wall == '#') {
    _x++;
    _x_coord++;
  }
}

void Enemy::displayToken() {
  mvwaddch(_curwin, _y, _x, _playerToken);
  wrefresh(_curwin);
}






void Enemy::changeHealth(string obj = NULL) {
  if(obj == "Potion") {
    _health+=5;
  }
}

int Enemy::getHealth() {
  return _health;
}
