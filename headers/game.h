#pragma once
#include <ncurses.h>
#include <vector>
#include <string>


using namespace std;


class Game {
  public:

    Game();
    void createInventory();
    void createHUD();
    void getMaxWindowSize(int xmax, int ymax);
    void updateInventoryWindow(vector<string> items);
    void delMenuWindow();
    void delHUDWindow();
    void playerHealthBar(int life);
    void playerExp(float exp);
    void playerAttackStat(int att);
    void updateStatusBar(int life, float exp, int att);
    bool gameOver(int life);

  private:
    WINDOW *_MenuWIN;
    WINDOW *_HUDWIN;
    int _xMax, _yMax;
    int _menuItemsY = 1;
    bool _gameOver = false;



};