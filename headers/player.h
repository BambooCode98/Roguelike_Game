#pragma once
#include <ncurses.h>
#include <string>


using namespace std;


class Player {
  public:

    Player(int y, int x, char playerToken, WINDOW *window);
    void displayToken();
    void mvPlayerUp();
    void mvPlayerDown();
    void mvPlayerLeft();
    void mvPlayerRight();
    void getMaxWindowSize(int xmax, int ymax);
    int getmv();
    void getCoordinates();
    void checkForWalls(string dir);
    void checkForObjects();


  private:
    char _playerToken;
    int _x,_y;
    WINDOW *_curwin;
    int _xMax, _yMax;
    int _xMove, _yMove;
    int _x_coord, _y_coord;
    string _direction;
};