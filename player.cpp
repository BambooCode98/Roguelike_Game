#include <string>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <ncurses.h>
#include "player.h"

using namespace std;


Player::Player(int y, int x, char playerToken, WINDOW *window) {
  _x = x;
  _y = y;
  _playerToken = playerToken;
  _curwin = window;
  _xMove = _yMove = 0;
}

void Player::getMaxWindowSize(int xmax, int ymax) {

  //get window size for outer bounds detection
  _xMax = xmax;
  _yMax = ymax;
}

void Player::mvPlayerUp() {
  mvwaddch(_curwin,_y,_x,'.');
  _y--;
  // _y_coord--;
  checkForWalls("up");
  checkForObjects();


  //prevent going offscreen
  if(_y <= 1) _y = 1;
}

void Player::mvPlayerDown() {
  mvwaddch(_curwin,_y,_x,'.');
  _y++;
  checkForWalls("down");
  checkForObjects();

  //prevent going offscreen
  if(_y >= _yMax-2) _y = _yMax-2;
}

void Player::mvPlayerLeft() {
  mvwaddch(_curwin,_y,_x,'.');
  _x--;
  // _x_coord--;
  checkForWalls("left");
  checkForObjects();


  //prevent going offscreen
  if(_x <= 1) _x = 1;
}

void Player::mvPlayerRight() {
  mvwaddch(_curwin,_y,_x,'.');
  _x++;
  // _x_coord++;
  checkForWalls("right");
  checkForObjects();


  //prevent going offscreen
  if(_x >= _xMax-2) _x = _xMax-2;
}

int Player::getmv() {
  int key = wgetch(_curwin);
      if(key == KEY_UP) {
      mvPlayerUp();
    } else if (key == KEY_DOWN) {
      mvPlayerDown();
      wrefresh(_curwin);
    } else if (key == KEY_RIGHT) {
      mvPlayerRight();
    } else if (key == KEY_LEFT) {
      mvPlayerLeft();
    }
    return key;
}

void Player::getCoordinates() {
  getyx(_curwin, _y_coord, _x_coord);
  mvwprintw(_curwin,_yMax/1.5,_xMax/1.5, "_y_coord: %d _x_coord: %d", _y_coord, _x_coord);
}

void Player::checkForObjects() {
  int object = mvwinch(_curwin,_y,_x);
  mvwprintw(_curwin,_yMax/1.2,_xMax/1.5,"object num: %d", object);
  // if(object == int('E')) {
  //   mvwprintw(_curwin,_yMax/1.1,_xMax/1.5,"Hit enemy");
  // }
  switch(object) {
    case int('E'):
      mvwprintw(_curwin,_yMax/1.1,_xMax/1.5,"Hit enemy");
      break;
    case int('P'):
      mvwprintw(_curwin,_yMax/1.1,_xMax/1.5,"Potion Acquired!");
      break;
  }
}

void Player::checkForWalls(string dir) {
  getCoordinates();
  int wall = mvwinch(_curwin,_y,_x) & A_CHARTEXT;
  // wprintw(_curwin,"%d", wall);
  mvwprintw(_curwin,_yMax/1.3,_xMax/1.5, "_y: %d _x: %d", _y, _x);

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

void Player::displayToken() {
  mvwaddch(_curwin, _y, _x, _playerToken);
  wrefresh(_curwin);
}

