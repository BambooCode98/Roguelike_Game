#include <string>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <ncurses.h>
#include "player.h"




Player::Player(int y, int x, char playerToken, WINDOW *window) {
  _x = x;
  _y = y;
  _playerToken = playerToken;
  _curwin = window;
}

void Player::setMaxWindowSize(int xmax, int ymax) {
  _xMax = xmax;
  _yMax = ymax;
}

void Player::mvPlayerUp() {
  mvwaddch(_curwin,_y,_x,' ');
  _y--;
  if(_y < 0) _y = _yMax;
}

void Player::mvPlayerDown() {
  mvwaddch(_curwin,_y,_x,' ');
  _y++;
  if(_y > _yMax) _y = 0;
}

void Player::mvPlayerLeft() {
  mvwaddch(_curwin,_y,_x,' ');
  _x--;
  if(_x < 0) _x = _xMax;
}

void Player::mvPlayerRight() {
  mvwaddch(_curwin,_y,_x,' ');
  _x++;
  if(_x > _xMax) _x = 0;
}

int Player::getmv() {
  int movespot = wgetch(_curwin);
      if(movespot == KEY_UP) {
      // mvwprintw(_curwin,1,1,"up arrow pressed \n");
      // wrefresh(_curwin);
      mvPlayerUp();
    } else if (movespot == KEY_DOWN) {
      // mvwprintw(_curwin,1,1,"down arrow pressed \n");
      // wrefresh(_curwin);
      mvPlayerDown();

    } else if (movespot == KEY_RIGHT) {
      // mvwprintw(_curwin,1,1,"right arrow pressed \n");
      // wrefresh(_curwin);
      mvPlayerRight();

    } else if (movespot == KEY_LEFT) {
      // mvwprintw(_curwin,1,1,"left arrow pressed \n");
      // wrefresh(_curwin);
      mvPlayerLeft();

    }
    return movespot;
}


void Player::displayToken() {
  mvwaddch(_curwin, _y, _x, _playerToken);
  wrefresh(_curwin);
}

