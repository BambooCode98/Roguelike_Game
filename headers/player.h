#pragma once
#include <vector>
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
    int  getmv();
    void getCoordinates();
    void checkForWalls(string dir);
    void checkForObjects();
    vector<string> updatePlayerInventory();
    void useItem(int num);
    void addHealth(string obj);
    void addAttack(string obj);
    void addExp(string obj);
    int  getHealth();
    int  getExp();
    int  getAttack();


  private:
    char _playerToken;
    int _x,_y;
    WINDOW *_curwin;
    int _xMax, _yMax;
    int _xMove, _yMove;
    int _x_coord, _y_coord;
    string _direction;
    string _item;
    vector<string> _itemList;
    bool _inventory_full = false;

    //status variables
    int _health = 20;
    int _maxHealth = 20;
    // bool _fullHealth = true;
    int _attack = 1;
    float _exp = 0;
};