#pragma once
#include <ncurses.h>


class Player {
  public:

    Player(int y, int x, char playerToken, WINDOW *window);
    void displayToken();
    void mvPlayerUp();
    void mvPlayerDown();
    void mvPlayerLeft();
    void mvPlayerRight();
    void setMaxWindowSize(int xmax, int ymax);
    int getmv();


  private:
    char _playerToken;
    int _x,_y;
    WINDOW *_curwin;
    int _xMax, _yMax;
};