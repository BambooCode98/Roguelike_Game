#include <string>
#include <algorithm>
#include <vector>
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
      // mvwprintw(_curwin,_yMax-5,_xMax-5, "%d",key);
      if(key == KEY_UP) {
      mvPlayerUp();
    } else if (key == KEY_DOWN) {
      mvPlayerDown();
      // wrefresh(_curwin);
    } else if (key == KEY_RIGHT) {
      mvPlayerRight();
    } else if (key == KEY_LEFT) {
      mvPlayerLeft();
    } else if (key == int('1')) {
      useItem(1);
    } else if (key == int('2')) {
      useItem(2);
    } else if (key == int('3')) {
      useItem(3);
    } else if (key == int('4')) {
      useItem(4);
    } else if (key == int('5')) {
      useItem(5);
    } else if (key == int('6')) {
      useItem(6);
    } else if (key == int('7')) {
      useItem(7);
    }
    return key;
}

void Player::getCoordinates() {
  getyx(_curwin, _y_coord, _x_coord);
  // mvwprintw(_curwin,_yMax/1.5,_xMax/1.5, "_y_coord: %d _x_coord: %d", _y_coord, _x_coord);
}

void Player::checkForObjects() {
  int object = mvwinch(_curwin,_y,_x);
  switch(object) {
    case int('E'):
      mvwprintw(_curwin,_yMax-5,5,"                 ");
      mvwprintw(_curwin,_yMax-5,5,"Hit enemy.");
      wrefresh(_curwin);
      _health-=5;
      break;
    case int('P'):
      if(_itemList.size() < 7) {
        mvwprintw(_curwin,_yMax-5,5,"                 ");
        mvwprintw(_curwin,_yMax-5,5,"Potion Acquired!");
        _itemList.push_back("Potion");
        wrefresh(_curwin);
      } else {
        mvwprintw(_curwin,_yMax-5,5,"                 ");
        mvwprintw(_curwin,_yMax-5,5,"Empty your inventory first.");
      }
      break;
    case int('S'):
      if(_itemList.size() < 7) {
        mvwprintw(_curwin,_yMax-5,5,"                 ");
        mvwprintw(_curwin,_yMax-5,5,"Sword Acquired!");
        _itemList.push_back("Sword");
        wrefresh(_curwin);
      } else {
        mvwprintw(_curwin,_yMax-5,5,"                 ");
        mvwprintw(_curwin,_yMax-5,5,"Empty your inventory first.");
      }
      break;
  }
}

void Player::checkForWalls(string dir) {
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

void Player::displayToken() {
  mvwaddch(_curwin, _y, _x, _playerToken);
  wrefresh(_curwin);
}




vector<string> Player::updatePlayerInventory()  {
  // vector<string> items;
  // _itemList.push_back(_item);
  // refresh();
  // int r = 0;
  //   mvwprintw(_curwin,LINES-_itemList.size(),5,"                       ");
  // for(string i: _itemList) {
  //   mvwprintw(_curwin,LINES-_itemList.size(),5,"vector: %s, length: %d", i.c_str(), _itemList.size());

  // }

  return _itemList;
}


void Player::useItem(int num) {
  if(_itemList.size() == 0) {
    mvwprintw(_curwin,LINES/1.4,COLS/1.75,"There is nothing in your inventory!");
  } else {
    string item;
    item = _itemList[num-1];
    
    if(item == "Potion" && _health < _maxHealth) {
      addHealth("Potion");
      mvwprintw(_curwin, _yMax-3, 5,"You used the %s.", _itemList[num-1].c_str());
      _itemList.erase(_itemList.begin()+(num-1));
    } else if(item == "Potion" && _health >= _maxHealth) {
      mvwprintw(_curwin,_yMax-4,5,"Can't use potion!");
    }
    if(item == "Sword") {
      addAttack("Sword");
      addExp("Sword");
      mvwprintw(_curwin, _yMax-3, 5,"You used the %s.", _itemList[num-1].c_str());
      _itemList.erase(_itemList.begin()+(num-1));
    }
  }
}


void Player::addHealth(string obj = NULL) {
  if(obj == "Potion" && _health < _maxHealth) {
    _health+=5;
  } else {
    mvwprintw(_curwin,_yMax-4,5,"Already have max health!");
  }
}

void Player::addAttack(string obj = NULL) {
  if(obj == "Sword") {
    _attack+=1;
  }
}

void Player::addExp(string obj = NULL) {
  if(obj == "Sword") {
    _exp+=0.5;
  }
}

int Player::getHealth() {
  return _health;
}

int Player::getAttack() {
  return _attack;
}

int Player::getExp() {
  return _exp;
}
