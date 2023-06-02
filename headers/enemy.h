#pragma once
#include <vector>
#include <ncurses.h>
#include <string>


using namespace std;


class Enemy {
  public:

    Enemy(int y, int x, char enemyToken, WINDOW *window,int health, int gExp);
    void displayToken();
    // void mvPlayerUp();
    // void mvPlayerDown();
    // void mvPlayerLeft();
    // void mvPlayerRight();
    // void getMaxWindowSize(int xmax, int ymax);
    // void getmv();
    // void getCoordinates();
    void checkForWalls(string dir);
    // void checkForObjects();
    // vector<string> updatePlayerInventory();
    // void useItem(int num);
    // void changeHealth(string obj);
    // int getHealth();


  private:
    char _playerToken;
    int _x,_y;
    WINDOW *_curwin;
    int _xMax, _yMax;
    int _xMove, _yMove;
    int _x_coord, _y_coord;
    string _direction;

    //status variables
    int _health;
    int _gExp;
};