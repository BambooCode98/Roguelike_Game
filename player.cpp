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
  mvwaddch(_curwin,_y,_x,' ');
  _y--;
  checkForCollisions("up");

  // _direction = "up";
  // checkForCollisions("_y", "up");
  // if(winch(_curwin) == '#') {
  //   _y+=1;
  // }


  //prevent going offscreen
  if(_y <= 1) _y = 1;
}

void Player::mvPlayerDown() {
  mvwaddch(_curwin,_y,_x,' ');
  _y++;
  // checkForCollisions();
  // chtype yselect = mvwinch(_curwin,0,0)&A_CHARTEXT;
  // if( yselect== char(35)) {
  //   wprintw(_curwin, "%d", mvwinch(_curwin,1,0)&A_CHARTEXT);
  //   _y--;
  // }
  checkForCollisions("down");
  //prevent going offscreen
  if(_y >= _yMax-2) _y = _yMax-2;
}

void Player::mvPlayerLeft() {
  mvwaddch(_curwin,_y,_x,' ');
  _x--;
  checkForCollisions("left");


  //prevent going offscreen
  if(_x <= 1) _x = 1;
}

void Player::mvPlayerRight() {
  mvwaddch(_curwin,_y,_x,' ');
  _x++;
  // _direction = "right";
  // checkForCollisions("_x", "right");
  // if(winch(_curwin) == '#') {
  //   _x-=1;
  // }
  checkForCollisions("right");



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
}

void Player::checkForCollisions(string dir) {
  int wall = mvwinch(_curwin,_y,_x) & A_CHARTEXT;
  // wprintw(_curwin,"%d", wall);
  // wrefresh(_curwin);
  if(dir == "down" && wall == '#') {
    _y--;
  } else if(dir == "up" && wall == '#') {
    _y++;
  } else if(dir == "right" && wall == '#') {
    _x--;
  } else if(dir == "left" && wall == '#') {
    _x++;
  }
  // switch(wall) {
  //   case '#':
  //     _y--;
  //     // wrefresh(_curwin);
  //     // wprintw(_curwin,"hi");
  //   break;
  // }
  // if(_y_coord+2 && int(wall)) {
  //   _y--;
  // }
}

void Player::displayToken() {
  mvwaddch(_curwin, _y, _x, _playerToken);
  wrefresh(_curwin);
}

