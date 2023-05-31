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
    void PlayerHealthBar(int life);
    void updateStatusBar(int life);

  private:
    WINDOW *_MenuWIN;
    WINDOW *_HUDWIN;
    int _xMax, _yMax;
    // float _menuItemsY = 1;



};